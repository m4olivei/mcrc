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
 * Implements hook_preprocess_html().
 */
function wise_preprocess_html(&$vars) {

  if (drupal_is_front_page()) {
    $vars['head_title_array']['title'] = t('Home');
    $vars['head_title'] = implode(' | ', $vars['head_title_array']);
  }
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

  // Hide the title on blog pages, it goes with the banner.
  if (is_blog_home()) {
    $vars['title'] = FALSE;
  }
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

/**
 * Implements hook_page_alter().
 */
function wise_page_alter(&$page) {

  // Tweak the search form on the search page to be an input-append.
  if (isset($page['content']['system_main']['search_form']['basic'])) {
    $search_form = &$page['content']['system_main']['search_form']['basic'];

    // Put together the textfield and button.
    unset($search_form['#attributes']);
    unset($search_form['keys']['#theme_wrappers']);
    $input_append = '<div class="input-append">';
    $input_append .= drupal_render($search_form['keys']);
    $input_append .= drupal_render($search_form['submit']);
    $input_append .= '</div>';

    $search_form['combined'] = array(
      '#markup' => $input_append,
    );
  }
}