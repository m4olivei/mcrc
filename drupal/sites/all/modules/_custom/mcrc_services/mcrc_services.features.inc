<?php
/**
 * @file
 * mcrc_services.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function mcrc_services_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function mcrc_services_node_info() {
  $items = array(
    'service' => array(
      'name' => t('Service'),
      'base' => 'node_content',
      'description' => t('A single service at Mountainview CRC.  Each service stores title, date, description, pastor, audio, etc. detailing a service (past or future) at Mountainview CRC.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
