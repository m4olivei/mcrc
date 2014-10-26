<?php
/**
 * @file
 * mcrc_notify.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function mcrc_notify_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
