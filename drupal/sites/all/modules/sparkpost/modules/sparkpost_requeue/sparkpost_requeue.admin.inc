<?php

/**
 * @file
 * Admin settings for sparkpost requeue.
 */

/**
 * Menu callback for the admin settings form.
 */
function sparkpost_requeue_admin_settings() {
  $form['sparkpost_requeue_enable'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable sparkpost requeue'),
    '#default_value' => variable_get('sparkpost_requeue_enable', FALSE),
  );
  $form['sparkpost_requeue_max_retries'] = array(
    '#type' => 'textfield',
    '#title' => t('Max number of retries of a message'),
    '#default_value' => variable_get('sparkpost_requeue_max_retries', 10),
    '#element_validate' => array('element_validate_integer_positive'),
    '#states' => array(
      'invisible' => array(
        ':input[name="sparkpost_requeue_enable"]' => array(
          'checked' => FALSE,
        ),
      ),
    ),
  );
  $form['sparkpost_requeue_minimum_time'] = array(
    '#type' => 'textfield',
    '#title' => t('Minimum time between retries in seconds.'),
    '#default_value' => variable_get('sparkpost_requeue_minimum_time', 300),
    '#element_validate' => array('element_validate_integer_positive'),
    '#states' => array(
      'invisible' => array(
        ':input[name="sparkpost_requeue_enable"]' => array(
          'checked' => FALSE,
        ),
      ),
    ),
  );
  return system_settings_form($form);
}
