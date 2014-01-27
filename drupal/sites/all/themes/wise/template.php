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

  if (drupal_is_front_page()) {
    drupal_set_title(t('Life at Mountainview'));
  }

  // Change the title of the user page
  if (user_is_anonymous() && $_GET['q'] == 'user') {
    drupal_set_title(t('Members Log in'));
  }

  // Throw a search box up in there
  $vars['search_box'] = wise_get_search_box();
}

/**
 * Implements hook_preprocess_node().
 */
function wise_preprocess_node(&$vars) {
  $node = $vars['node'];

  if (!in_array($node->type, array('service'))) {
    $vars['image'] = '';
    if (!empty($vars['content']['field_image'][0])) {
      hide($vars['content']['field_image']);
      $vars['image'] = render($vars['content']['field_image'][0]);
    }
  }

  if (!empty($vars['content']['field_service_audio'])) {
    $vars['classes_array'][] = 'has-audio';
  }

  // @todo override date if field is available
  $vars['date'] = format_date($node->created, 'short');

  $vars['submitted'] = t('Posted !datetime', array('!datetime' => $vars['date']));
  if ($node->type == 'blog_post') {
    $account = user_load($node->uid);
    $vars['name'] = l(check_plain(format_username($node)), 'blog/author/' . $account->name);
    $vars['submitted'] = t('Posted on !datetime by !username', array('!datetime' => $vars['date'], '!username' => $vars['name']));
  }
}

/**
 * Implements hook_preprocess_views_view_table().
 */
function wise_preprocess_views_view_table(&$vars) {
  $vars['classes_array'][] = 'table';
  $vars['classes_array'][] = 'table-striped';
  $vars['classes_array'][] = 'table-hover';
}
