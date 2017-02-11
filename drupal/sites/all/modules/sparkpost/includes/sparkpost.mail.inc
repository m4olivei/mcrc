<?php

/**
 * @file
 * Implements Sparkpost as a Drupal MailSystemInterface
 */

/**
 * Modify the drupal mail system to use Sparkpost when sending emails.
 */
class SparkpostMailSystem implements MailSystemInterface {

  /**
   * Concatenate and wrap the email body for either plain-text or HTML emails.
   *
   * @param array $message
   *   A message array, as described in hook_mail_alter().
   *
   * @return array
   *   The formatted $message.
   */
  public function format(array $message) {
    // Join the body array into one string.
    if (is_array($message['body'])) {
      $message['body'] = implode("\n\n", $message['body']);
    }

    // Sanitize email subject.
    $message['subject'] = check_plain($message['subject']);
    // Remove newlines.
    $message['subject'] = preg_replace('/[\r\n]+/', '', $message['subject']);

    return $message;
  }

  /**
   * Send the email message.
   *
   * @see drupal_mail()
   *
   * @param array $message
   *   A message array, as described in hook_mail_alter().
   *
   * @return bool
   *   TRUE if the mail was successfully accepted, otherwise FALSE.
   */
  public function mail(array $message) {
    // Apply input format to body.
    $format = variable_get('sparkpost_filter_format', '');
    if (!empty($format)) {
      $message['body'] = check_markup($message['body'], $format);
    }

    // Prepare headers, defaulting the reply-to to the from address since
    // Sparkpost needs the from address to be configured separately.
    // Note that only Reply-To and X-* headers are allowed.
    $headers = isset($message['headers']) ? $message['headers'] : array();
    if (isset($message['params']['sparkpost']['header'])) {
      $headers = $message['params']['sparkpost']['header'] + $headers;
    }
    if (!empty($message['from']) && empty($headers['Reply-To'])) {
      $headers['Reply-To'] = $message['from'];
    }

    // Extract an array of recipients.
    $to = sparkpost_get_to($message['to']);

    // Prepare list of Cc and Bcc recipients.
    $cc = $bcc = array();
    if (isset($headers['Cc'])) {
      $cc = sparkpost_get_cc($headers['Cc'], $to);
    }
    if (isset($headers['Bcc'])) {
      $bcc = sparkpost_get_cc($headers['Bcc'], $to);
    }
    $to = array_merge($to, $cc, $bcc);

    // Get sender.
    $from = sparkpost_from();

    $reply_to = isset($headers['Reply-To']) ? $headers['Reply-To'] : NULL;
    $headers = sparkpost_allowed_headers($headers);

    // Prepare attachments.
    $attachments = array();
    if (isset($message['attachments']) && !empty($message['attachments'])) {
      foreach ($message['attachments'] as $attachment) {
        if (is_file($attachment)) {
          $attachments[] = $this->getAttachmentStruct($attachment);
        }
      }
    }

    // The Mime Mail module (mimemail) expects attachments as an array of file
    // arrays in $message['params']['attachments']. As many modules assume you
    // will be using Mime Mail to handle attachments, we need to parse this
    // array as well.
    if (isset($message['params']['attachments']) && !empty($message['params']['attachments'])) {
      foreach ($message['params']['attachments'] as $attachment) {
        if (isset($attachment['uri'])) {
          $attachment_path = drupal_realpath($attachment['uri']);
          if (is_file($attachment_path)) {
            $struct = $this->getAttachmentStruct($attachment_path);
            // Allow for customised filenames.
            if (!empty($attachment['filename'])) {
              $struct['name'] = $attachment['filename'];
            }
            $attachments[] = $struct;
          }
        }
        // Support attachments that are directly included without a file in the
        // filesystem.
        elseif (isset($attachment['filecontent'])) {
          $attachments[] = array(
            'type' => $attachment['filemime'],
            'name' => $attachment['filename'],
            'data' => chunk_split(base64_encode($attachment['filecontent']), 76, "\n"),
          );
        }
      }
      // Remove the file objects from $message['params']['attachments'].
      // (This prevents double-attaching in the drupal_alter hook below.)
      unset($message['params']['attachments']);
    }

    // Account for the plaintext parameter provided by the mimemail module.
    $plain_text = empty($message['params']['plaintext']) ? drupal_html_to_text($message['body']) : $message['params']['plaintext'];

    $overrides = isset($message['params']['sparkpost']['overrides']) ? $message['params']['sparkpost']['overrides'] : array();
    $sparkpost_message = $overrides + array(
      'html' => $message['body'],
      'text' => $plain_text,
      'subject' => $message['subject'],
      'from' => [
        'name' => isset($message['params']['sparkpost']['from_name']) ? $message['params']['sparkpost']['from_name'] : $from['name'],
        'email' => $from['email'],
      ],
      'replyTo' => $reply_to,
      'recipients' => $to,
      // SparkPost doesn't allow campaigns longer than 64 characters.
      'campaign' => substr($message['id'], 0, 64),
      'attachments' => $attachments,
      'customHeaders' => $headers,
      // See #2793291 - Allow marking email as transactional to not have
      // Unsubscribe links in email client.
      'transactional' => TRUE,
    );

    // Allow other modules to alter the Sparkpost message.
    drupal_alter('sparkpost_mail', $sparkpost_message, $message);

    $message_wrapper = new SparkpostMessageWrapper($sparkpost_message, $message);

    // Check if we are sending async or not.
    if (variable_get('sparkpost_send_async', FALSE)) {
      // If we are sending async, add it to the queue, and return success.
      /** @var DrupalQueueInterface $queue */
      $queue = DrupalQueue::get(SPARKPOST_QUEUE_NAME);
      $queue->createItem($message_wrapper);
      return TRUE;
    }

    return sparkpost_mailsend($message_wrapper);
  }

  /**
   * Return an array structure for a message attachment.
   *
   * @param string $path
   *   Attachment path.
   *
   * @return array
   *   Attachment structure.
   *
   * @throws Exception
   */
  public function getAttachmentStruct($path) {
    $struct = array();

    if (!@is_file($path)) {
      throw new Exception($path . ' is not a valid file.');
    }

    $filename = basename($path);

    $file_buffer = file_get_contents($path);
    $file_buffer = chunk_split(base64_encode($file_buffer), 76, "\n");

    $mime_type = file_get_mimetype($path);
    if (!$this->isValidContentType($mime_type)) {
      throw new Exception($mime_type . ' is not a valid content type.');
    }

    $struct['type'] = $mime_type;
    $struct['name'] = $filename;
    $struct['data'] = $file_buffer;

    return $struct;
  }

  /**
   * Helper to determine if an attachment is valid.
   *
   * @param string $file_type
   *   The file mime type.
   *
   * @return bool
   *   True or false.
   */
  protected function isValidContentType($file_type) {
    $valid_types = array(
      'image/',
      'text/',
      'application/pdf',
      'application/x-zip',
    );
    drupal_alter('sparkpost_valid_attachment_types', $valid_types);

    foreach ($valid_types as $vct) {
      if (strpos($file_type, $vct) !== FALSE) {
        return TRUE;
      }
    }

    return FALSE;
  }

}
