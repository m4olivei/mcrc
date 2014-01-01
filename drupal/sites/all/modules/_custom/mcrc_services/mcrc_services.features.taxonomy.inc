<?php
/**
 * @file
 * mcrc_services.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function mcrc_services_taxonomy_default_vocabularies() {
  return array(
    'pastors' => array(
      'name' => 'Pastors',
      'machine_name' => 'pastors',
      'description' => 'Pastors who preach at Mountainview CRC.',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
  );
}
