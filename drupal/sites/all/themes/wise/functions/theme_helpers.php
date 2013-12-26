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