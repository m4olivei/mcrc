<?php

/**
 * @file
 * Admin callbacks.
 */

/**
 * Administrative settings.
 *
 * @param array $form
 *   Form render array.
 * @param array $form_state
 *   Array containing form state values.
 *
 * @return array
 *   An array containing form items to place on the module settings page.
 */
function sparkpost_admin_settings($form, &$form_state) {
  $key = variable_get('sparkpost_api_key');
  $form['sparkpost_api_key'] = array(
    '#title' => t('Sparkpost API Key'),
    '#type' => 'textfield',
    '#description' => t('Create or grab your API key from the !link.',
      array('!link' => l(t('Sparkpost settings'), 'https://app.sparkpost.com/account/credentials'))),
    '#default_value' => $key,
  );

  $library_exists = class_exists('\SparkPost\SparkPost');

  if (!$library_exists) {
    drupal_set_message(t('The Sparkpost PHP library is not installed. Please see installation directions in README.md'),
      'warning');
  }

  if ($key && $library_exists) {
    $mailsystem_config_keys = mailsystem_get();
    $in_use = FALSE;
    $usage_rows = array();
    foreach ($mailsystem_config_keys as $key => $sys) {
      if ($sys === 'SparkpostMailSystem' && $key != 'sparkpost_test') {
        $in_use = TRUE;
        $usage_rows[] = array(
          $key,
          $sys,
        );
      }
    }
    if ($in_use) {
      $usage_array = array(
        '#theme' => 'table',
        '#header' => array(
          t('Module Key'),
          t('Mail System'),
        ),
        '#rows' => $usage_rows,
      );
      $form['sparkpost_status'] = array(
        '#type' => 'markup',
        '#markup' => t('Sparkpost is currently configured to be used by the following Module Keys. To change these settings or configure additional systems to use Sparkpost, use !link.<br /><br />!table',
          array(
            '!link' => l(t('Mail System'), 'admin/config/system/mailsystem'),
            '!table' => drupal_render($usage_array),
          )),
      );
    }
    elseif (!$form_state['rebuild']) {
      drupal_set_message(t('PLEASE NOTE: Sparkpost is not currently configured for use by Drupal. In order to route your email through Sparkpost, you must configure at least one MailSystemInterface (other than sparkpost) to use "SparkpostMailSystem" in !link, or you will only be able to send Test Emails through Sparkpost.',
        array('!link' => l(t('Mail System'), 'admin/config/system/mailsystem'))), 'warning');
    }

    $form['email_options'] = array(
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#title' => t('Email options'),
    );

    $from = sparkpost_from();
    $form['email_options']['sparkpost_from'] = array(
      '#title' => t('From address'),
      '#type' => 'textfield',
      '#description' => t('The sender email address. If this address has not been verified, messages will be queued and not sent until it is. This address will appear in the "from" field, and any emails sent through Sparkpost with a "from" address will have that address moved to the Reply-To field.'),
      '#default_value' => $from['email'],
    );
    $form['email_options']['sparkpost_from_name'] = array(
      '#type' => 'textfield',
      '#title' => t('From name'),
      '#default_value' => $from['name'],
      '#description' => t('Optionally enter a from name to be used.'),
    );
    $formats = filter_formats();
    $options = array('' => t('-- Select --'));
    foreach ($formats as $v => $format) {
      $options[$v] = $format->name;
    }
    $form['email_options']['sparkpost_filter_format'] = array(
      '#type' => 'select',
      '#title' => t('Input format'),
      '#description' => t('If selected, the input format to apply to the message body before sending to the Sparkpost API.'),
      '#options' => $options,
      '#default_value' => array(variable_get('sparkpost_filter_format', 'full_html')),
    );
  }
  return system_settings_form($form);
}

/**
 * Javascript callback for the sparkpost_admin_settings form.
 *
 * @param array $form
 *   a drupal form
 * @param array $form_state
 *   drupal form_state
 *
 * @return array
 *   a form section
 */
function sparkpost_admin_settings_form_callback($form, &$form_state) {
  return $form['asynchronous_options'];
}

/**
 * Return a form for sending a test email.
 */
function sparkpost_test_form($form, &$form_state) {
  drupal_set_title(t('Send test email'));

  $form['sparkpost_test_address'] = array(
    '#type' => 'textfield',
    '#title' => t('Email address to send a test email to'),
    '#default_value' => variable_get('site_mail', ''),
    '#description' => t('Type in an address to have a test email sent there.'),
    '#required' => TRUE,
  );
  $form['sparkpost_test_body'] = array(
    '#type' => 'textarea',
    '#title' => t('Test body contents'),
    '#default_value' => t('If you receive this message it means your site is capable of using Sparkpost to send email. This url is here to test click tracking: !link',
      array('!link' => l(t('link'), 'http://www.drupal.org/project/sparkpost'))),
  );
  $form['include_attachment'] = array(
    '#title' => t('Include attachment'),
    '#type' => 'checkbox',
    '#description' => t('If checked, the Drupal icon will be included as an attachment with the test email.'),
    '#default_value' => TRUE,
  );

  $form['test_submit'] = array(
    '#type' => 'submit',
    '#value' => t('Send test email'),
  );
  $form['test_cancel'] = array(
    '#type' => 'link',
    '#href' => 'admin/config/services/sparkpost',
    '#title' => t('Cancel'),
  );

  return $form;
}

/**
 * Submit handler for sparkpost_test_form(), sends the test email.
 */
function sparkpost_test_form_submit($form, &$form_state) {
  // If an address was given, send a test email message.
  $test_address = $form_state['values']['sparkpost_test_address'];
  global $language;
  $params['subject'] = t('Drupal Sparkpost test email');
  $params['body'] = $form_state['values']['sparkpost_test_body'];
  $params['include_attachment'] = $form_state['values']['include_attachment'];
  $mailsystem = mailsystem_get();
  // Check for empty mailsystem config for Sparkpost:
  $primary_config = empty($mailsystem['sparkpost_test']) ? 'sparkpost' : 'sparkpost_test';
  if (empty($mailsystem[$primary_config])) {
    drupal_set_message(t('Automatically setting Sparkpost tests to go through Sparkpost API: SparkpostMailSystem was not previously configured in Mail System.'));
    mailsystem_set(array('sparkpost_test' => 'SparkpostMailSystem'));
  }
  // Check for wrong mailsystem config for Sparkpost, if not empty, and issue a
  // warning:
  elseif ($mailsystem[$primary_config] != 'SparkpostMailSystem') {
    drupal_set_message(
      t('Mail System is configured to send Sparkpost Test messages through %system, not Sparkpost. To send tests through Sparkpost, go to !link and change the setting.',
        array(
          '%system' => $mailsystem['sparkpost_test'],
          '!link' => l(t('Sparkpost'), 'https://sparkpostapp.com/templates'))),
      'warning');
    // Hack because we are apparently formatting the body differently than
    // default drupal messages.
    $params['body'] = array('0' => $params['body']);
  }
  $result = drupal_mail('sparkpost', 'test', $test_address, $language, $params);
  if (isset($result['result']) && $result['result'] == 'true') {
    drupal_set_message(t('Sparkpost test email sent from %from to %to.', array('%from' => $result['from'], '%to' => $result['to'])), 'status');
  }
  else {
    $form_state['rebuild'] = TRUE;
  }
}
