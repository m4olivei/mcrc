<?php
/**
 * @file
 * Admin options for the OG module.
 */

/**
 * Settings form.
 */
function wise_og_settings() {
  $form = array();

  $publisher_id = variable_get('wise_og_publisher_id', '');
  $form['wise_og_publisher_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Faceboook publisher id'),
    '#description' => t('Set the Facebook publisher id, which is then set as the value for article:publisher.  The publisher id is the value at the end of your Facebook page URL, eg. https://www.facebook.com/<strong>publisherid</strong>'),
    '#default_value' => $publisher_id,
    '#required' => TRUE,
  );

  return system_settings_form($form);
}
