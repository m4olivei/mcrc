<?php
/**
 * @file
 * mcrc_publications.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function mcrc_publications_taxonomy_default_vocabularies() {
  return array(
    'publications' => array(
      'name' => 'Publications',
      'machine_name' => 'publications',
      'description' => 'Classify publications for access control.',
      'hierarchy' => 1,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
  );
}
