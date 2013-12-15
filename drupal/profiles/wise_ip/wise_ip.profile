<?php
/**
 * @file
 * Main file for the Wise & Hammer Installation profile.  Hooks and stuff to make stuff happen and stuff.
 */
// Profiler module includes statement - does some crazy stuff
!function_exists('profiler_v2') ? require_once('libraries/profiler/profiler.inc') : FALSE;
profiler_v2('wise_ip');

/**
 * Implements hook_form_FORM_ID_alter() for install_configure_form().
 *
 * Allows the profile to alter the site configuration form.
 */
function wise_ip_form_install_configure_form_alter(&$form, $form_state) {
  // Pre-populate the site name with the server name.
  $form['site_information']['site_name']['#default_value'] = $_SERVER['SERVER_NAME'];
  $form['site_information']['site_mail']['#default_value'] = 'dev@wiseandhammer.com';

  // Pre-populate the Site Maintenance Account
  $form['admin_account']['account']['name']['#default_value'] = 'root';
  $form['admin_account']['account']['mail']['#default_value'] = $form['site_information']['site_mail']['#default_value'];

  // Pre-populate the server settings
  $form['server_settings']['site_default_country']['#default_value'] = 'CA';
  $form['server_settings']['date_default_timezone']['#default_value'] = 'America/Toronto';

  // Turn off update notifications by default
  $form['update_notifications']['update_status_module']['#default_value'] = array();
}

/**
 * Implements hook_js_alter().
 * Remove the timezone js from the install profile configure form.
 */
function wise_ip_js_alter(&$javascript) {
  if (defined('MAINTENANCE_MODE') && MAINTENANCE_MODE == 'install' && $_GET['profile'] === 'wise_ip') {
    unset($javascript['misc/timezone.js']);
  }
}
