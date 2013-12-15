<?php
/**
 * @file
 * Contains the theme's functions to manipulate Drupal's default markup.
 * @todo hunt for styles and mixins that would be handy to add to the base theme
 * @todo hunt for util php functions that would be benificial to add
 * @todo responsive breakpoint mixins
 * @todo incorporate bootstrap 3 (last!)
 */

// Include any additional functions broken out into different files in the functions folder
// Load up our custom theme functions.
$functions_dir = dirname(__FILE__) . '/functions';
foreach (glob($functions_dir . '/*.php') as $filename) {
  include_once $filename;
}

/**
 * Implements hook_preprocess_page().
 */
function wise_preprocess_page(&$vars) {

  if (wise_is_live_reload()) {
    drupal_add_js('http://localhost:35729/livereload.js?snipver=1', array('type' => 'external'));
  }
}