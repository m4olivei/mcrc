<?php
/**
 * @file
 * Loaded only when needed by the Migrate module.  Classes implemented for migrate support should
 * be listed in the info file.
 */

/**
 * Implements hook_migrate_api().
 */
function mcrc_migrate_migrate_api() {
  return array(
    'api' => 2,
    'migrations' => array(
      'MCRCPastorTerm' => array('class_name' => 'MCRCPastorTermMigration'),
      'MCRCService' => array('class_name' => 'MCRCServiceMigration'),
      'MCRCUser' => array('class_name' => 'MCRCUserMigration'),
      'MCRCPublications' => array('class_name' => 'MCRCPublicationsMigration'),
      'MCRCBlog' => array('class_name' => 'MCRCBlogMigration'),
      'MCRCServiceItunes' => array('class_name' => 'MCRCServiceItunesMigration'),
    ),
  );
}