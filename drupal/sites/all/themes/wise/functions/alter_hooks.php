<?php
/**
 * @file
 */

/**
 * Alter the CSS by parsing the theme info file for excludes and actually exclude them
 * from the page.
 *
 * Taken from d.o/project/bootstrap
 */
function wise_css_alter(&$css) {
  $excludes = _wise_alter(wise_get_info('exclude'), 'css');
  $css = array_diff_key($css, $excludes);
}

/**
 * Loop through the files given that are each settings in the theme info file
 * and return all of them of the given $type.
 *
 * Taken from d.o/project/bootstrap
 */
function _wise_alter($files, $type) {
  $output = array();

  foreach($files as $key => $value) {
    if (isset($files[$key][$type])) {
      foreach($files[$key][$type] as $file => $name) {
        $output[$name] = FALSE;
      }
    }
  }

  return $output;
}