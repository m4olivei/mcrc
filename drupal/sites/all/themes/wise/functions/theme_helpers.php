<?php
/**
 * @file
 * Aid in outputing HTML.
 */

/**
 * Return markup for the desktop menu.
 * @return string
 */
function wise_get_desktop_menu() {
  $config = array(
    'delta' => 'desktop',
    'menu_name' => 'main-menu',
    'parent_mlid' => 0,
    'title_link' => 0,
    'admin_title' => t('Main Menu'),
    'level' => 1,
    'follow' => 0,
    'depth' => 1,
    'expanded' => 0,
    'sort' => 0,
  );

  return _wise_menu_wrapper_markup($config, 'menu-drop-down');
}

/**
 * Return markup for the mobile menu.
 * @return string
 */
function wise_get_mobile_menu() {
  $config = array(
    'delta' => 'mobile',
    'menu_name' => 'main-menu',
    'parent_mlid' => 0,
    'title_link' => 0,
    'admin_title' => t('Main Menu'),
    'level' => 1,
    'follow' => 0,
    'depth' => 1,
    'expanded' => 0,
    'sort' => 0,
  );

  return _wise_menu_wrapper_markup($config, 'mobile-menu');
}

/**
 * Return markup for the secondary menu.
 * @return string
 */
function wise_get_secondary_navigation() {
  $config = array(
    'delta' => 'secondary-menu',
    'menu_name' => 'menu-secondary-menu',
    'parent_mlid' => 0,
    'title_link' => 0,
    'admin_title' => t('Secondary Menu'),
    'level' => 1,
    'follow' => 0,
    'depth' => 1,
    'expanded' => 0,
    'sort' => 0,
  );

  return _wise_menu_wrapper_markup($config, 'menu-drop-down');
}

/**
 * Markup for the member tools.
 */
function wise_get_member_tools() {
  global $user;

  $output = '';
  $name = format_username($user);

  if (user_is_logged_in()) {
    $output .= l('<i class="icon-user"></i>' . t('Welcome %user', array('%user' => $name)), 'user', array('attributes' => array('class' => array('welcome-link')), 'html' => TRUE));
    $output .= l('<i class="icon-unlock"></i>' . t('Log out'), 'user/logout', array('attributes' => array('class' => array('login-link')), 'html' => TRUE));
  }
  else {
    $output .= l('<i class="icon-lock"></i>' . t('Log in'), 'user', array('attributes' => array('class' => array('login-link')), 'html' => TRUE));
  }

  return $output;
}

/**
 * Helper function that takes the given config for a menu_block block and calls the necessary menu_block
 * module function to render that block.  Returns the menu_block with consistent wrapping markup.
 *
 * @param $config
 *  menu_block module config @see menu_tree_build().
 * @param $wrapper_class
 *  HTML class used in a wrapping div around the title and content.
 * @return string
 */
function _wise_menu_wrapper_markup($config, $wrapper_class) {
  $output = '';

  // Make sure menu_block module is enabled, otherwise this makes no sense.
  if (!function_exists('menu_tree_build')) {
    return $output;
  }
  $data = menu_tree_build($config);

  if (!empty($data['content'])) {
    $output = render($data['content']);

    if (!empty($data['subject'])) {
      $output = '<h2 class="element-focusable">' . $data['subject'] . '</h2>' . $output;
    }

    $output = '<div class="clearfix ' . $wrapper_class . '">' . $output . '</div>';
  }

  return $output;
}

/**
 * Get a custom themed search box.
 */
function wise_get_search_box() {
  $search_form = drupal_get_form('search_block_form');

  // Put together the textfield and button.
  unset($search_form['search_block_form']['#theme_wrappers']);
  $input_append = '<div class="input-append">';
  $input_append .= drupal_render($search_form['search_block_form']);
  $input_append .= drupal_render($search_form['actions']);
  $input_append .= '</div>';

  $search_form['combined'] = array(
    '#markup' => $input_append,
  );

  return render($search_form);
}

/**
 * Get the blog banner.
 */
function wise_get_blog_banner() {

  $output = '<div class="banner banner-blog">';
  $output .= '<img src="/' . drupal_get_path('theme', 'wise') . '/images/blog_header.jpg" />';
  $output .= '<div class="content">';
  if (is_blog_home()) {
    $output .= '<h1 class="title" id="page-title">' . t('Pastor\'s Keyboard') . '</h1>';
  }
  else {
    $output .= '<h1 class="title">' . t('Pastor\'s Keyboard') . '</h1>';
  }
  $output .= '<p>' . t('A weekly blog by Pastor Sid Couperus') . '</p>';
  $output .= '</div>';
  $output .= '</div>';

  return $output;
}

/**
 * Helper function to return if we are on the blog.
 */
function is_blog() {
  $ret = FALSE;

  if (is_blog_home()) {
    $ret = TRUE;
  }
  if (($node = menu_get_object()) && $node->type == 'blog_post') {
    $ret = TRUE;
  }
  if (drupal_match_path($_GET['q'], implode("\n", array('blog*')))) {
    $ret = TRUE;
  }

  return $ret;
}

function is_blog_home() {

  return $_GET['q'] == 'blog';
}