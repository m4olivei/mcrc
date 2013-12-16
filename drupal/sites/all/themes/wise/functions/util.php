<?php
/**
 * @file
 * General utility funcitons used by the theme.
 */

/**
 * Figure our what environment we are running in. Default is production.
 *
 * @return string
 */
function wise_get_environment() {
  $env = getenv('DRUPAL_ENVIRONMENT');
  return (!empty($env)) ? $env : 'production';
}

/**
 * Figure out if Live Reload is being used. Default is false.
 *
 * @return Boolean
 */
function wise_get_live_reload() {
  $live_reload = getenv('LIVE_RELOAD');
  return (!empty($live_reload) && $live_reload == 'true');
}

/**
 * Helper function to determine the environment.
 *
 * @param string $test
 *   The environment that is expected.
 * @return bool
 */
function wise_is_environment($test) {
  return (strtolower(wise_get_environment()) === strtolower($test));
}

/**
 * Helper function to determine if using LiveReload.
 *
 * @return bool
 */
function wise_is_live_reload() {
  return FALSE && (wise_is_environment('development') && wise_get_live_reload());
}

/**
 * Contextually add Bootstrap grid classes.  Inspired by drupal.org/project/ninesixty ns().
 *
 * The first parameter passed is the type, one of 'columns' or 'offset'.
 * The second parameter is the default unit.  All other parameters must
 * be set in pairs like so: "$variable, 3". The variable can be anything available
 * within a template file and the integer is the width set for the adjacent box
 * containing that variable.  Effectivly the first variable in the tuple is a evaluated
 * using !empty($variable).  If that evaluate to TRUE, the integer is subtracted from the
 * default unit.  Example usage:
 *
 *  class="<?php print wise_ns('columns', $sidebar_first, 4); ?>"
 *
 * If $sidebar_first contains data, the next parameter (integer) will be subtracted from
 * the default unit.
 */
function wise_ns() {
  $var_state = NULL;
  $matches = array();
  $args = func_get_args();
  $default = array_shift($args);

  // Get the type of class, i.e., 'span' or 'offset'
  // Also get the default unit for the type to be procesed and returned.
  preg_match('~^(span|offset)(\d+)$~', $default, $matches);
  if (empty($matches[1]) || empty($matches[2])) {
    return '';
  }
  list($type, $return_unit) = array($matches[1], $matches[2]);

  // Process the conditions.
  $flip_states = array('var' => 'int', 'int' => 'var');
  $state = 'var';
  foreach ($args as $arg) {
    if ($state == 'var') {
      $var_state = !empty($arg);
    }
    elseif ($var_state) {
      $return_unit = $return_unit - $arg;
    }
    $state = $flip_states[$state];
  }

  $output = '';
  // Anything below a value of 1 is not needed.
  if ($return_unit > 0) {
    $output = $type . $return_unit;
  }
  return $output;
}

/**
 * Get a custom theme setting.
 *
 * Taken from d.o/project/bootstrap
 */
function wise_get_info($setting_name, $theme = NULL) {
  // If no key is given, use the current theme if we can determine it.
  if (!isset($theme)) {
    $theme = !empty($GLOBALS['theme_key']) ? $GLOBALS['theme_key'] : '';
  }

  $output = array();

  if ($theme) {
    $themes = list_themes();
    $theme_object = $themes[$theme];

    // Create a list which includes the current theme and all its base themes.
    if (isset($theme_object->base_themes)) {
      $theme_keys = array_keys($theme_object->base_themes);
      $theme_keys[] = $theme;
    }
    else {
      $theme_keys = array($theme);
    }
    foreach ($theme_keys as $theme_key) {
      if (!empty($themes[$theme_key]->info[$setting_name])) {
        $output[$setting_name] = $themes[$theme_key]->info[$setting_name];
      }
    }
  }

  return $output;
}