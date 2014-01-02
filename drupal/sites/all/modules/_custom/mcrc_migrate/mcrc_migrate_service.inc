<?php
/**
 * @file
 * Migrate services into Drupal nodes.
 */

class MCRCServiceMigration extends DynamicMigration {

  /**
   *
   */
  function __construct() {
    parent::__construct();

    // Human-friendly description of migration process
    $this->description = t('Migrate Pastor names as taxonomy terms to be used in the Service migration.');

    // Create a map object for tracking the relationships between source rows
    // and their resulting Drupal objects. Pass the machine name
    // (MCRCService) of this migration to use in generating map and message tables.
    // And, pass schema definitions for the primary keys of the source and
    // destination - we need to be explicit for our source, but the destination
    // class knows its schema already.
    $this->map = new MigrateSQLMap($this->machineName,
        array(
          'id' => array(
            'type' => 'int',
            'length' => 10,
            'not null' => TRUE,
            'description' => 'Service ID',
          ),
        ),
        MigrateDestinationNode::getKeySchema()
      );

    // First, we set up a query for this data. Note that our source data
    // lives in a differnt database, on a connection defined in settings.php.  For this reason, we
    // use Database::getConnection instead of db_select, to specify the legacy DB as the DB to use.
    $query = Database::getConnection('default', 'mcrc_legacy')
      ->select('tblSermons', 's')
      ->fields('s', array('id', 'date_presented', 'pastor', 'title', 'date_uploaded', 'filename'));

    // Create a MigrateSource object, which manages retrieving the input data.
    $this->source = new MigrateSourceSQL($query);

    // Set up our destination - terms in the pastors vocabulary
    $this->destination = new MigrateDestinationNode('service');

    // Mappings
    $this->addFieldMapping('title', 'title');

    // @todo finish field mappings - duh.
  }
}