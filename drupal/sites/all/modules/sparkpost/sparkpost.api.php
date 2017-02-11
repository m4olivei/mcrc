<?php

/**
 * @file
 * Hooks provided by the sparkpost module.
 */

/**
 * Alter the Sparkpost message or the Drupal message array.
 *
 * @param array $sparkpost_message
 *   The array we are about the send to the Sparkpost API.
 * @param array $message
 *   The drupal_mail message the Sparkpost message was based on.
 *
 * @see drupal_mail()
 * @see sparkpost_mail()
 */
function hook_sparkpost_mail_alter($sparkpost_message, $message) {
  // Code to alter the message.
}

/**
 * Allows other modules to alter the allowed attachment file types.
 *
 * @param array $types
 *   An array of file types indexed numerically.
 */
function hook_sparkpost_valid_attachment_types_alter(&$types) {
  // Example, allow word docs:
  $types[] = 'application/msword';
  // Allow openoffice docs:
  $types[] = 'application/vnd.openxmlformats-officedocument.wordprocessingml.document';
}

/**
 * Act on a successfully sent message through Sparkpost.
 *
 * @param SparkpostMessageWrapperInterface $message_wrapper
 *   A SparkpostMessageWrapper object.
 *
 * @see SparkpostMessageWrapperInterface
 */
function hook_sparkpost_mailsend_success(SparkpostMessageWrapperInterface $message_wrapper) {
  // Do something with the result.
}

/**
 * Act on a message that failed to send through Sparkpost.
 *
 * @param SparkpostMessageWrapperInterface $message_wrapper
 *   A SparkpostMessageWrapper object.
 *
 * @see SparkpostMessageWrapperInterface
 */
function hook_sparkpost_mailsend_error(SparkpostMessageWrapperInterface $message_wrapper) {
  // Do something with the result.
}
