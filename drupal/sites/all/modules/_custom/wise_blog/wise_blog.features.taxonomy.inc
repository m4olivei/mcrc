<?php
/**
 * @file
 * wise_blog.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function wise_blog_taxonomy_default_vocabularies() {
  return array(
    'blog_post_category' => array(
      'name' => 'Blog Post Category',
      'machine_name' => 'blog_post_category',
      'description' => 'Categorize blog posts',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
  );
}
