<?php
/**
 * @file
 * Migrate Pastors in as taxonomy terms.
 */

class MCRCPastorTermMigration extends MCRCMigrateBase {

  /**
   * Initiate the migration for Pastor terms.
   *
   * There are four essential components to set up in your constructor:
   *  $this->source - An instance of a class derived from MigrateSource, this
   *    will feed data to the migration.
   *  $this->destination - An instance of a class derived from MigrateDestination,
   *    this will receive data that originated from the source and has been mapped
   *    by the Migration class, and create Drupal objects.
   *  $this->map - An instance of a class derived from MigrateMap, this will keep
   *    track of which source items have been imported and what destination objects
   *    they map to.
   *  Mappings - Use $this->addFieldMapping to tell the Migration class what source
   *    fields correspond to what destination fields, and additional information
   *    associated with the mappings.
   */
  function __construct() {
    parent::__construct();

    // Human-friendly description of migration process
    $this->description = t('Migrate Pastor names as taxonomy terms to be used in the Service migration.');

    // Create a map object for tracking the relationships between source rows
    // and their resulting Drupal objects. Pass the machine name
    // (MCRCPastorTerm) of this migration to use in generating map and message tables.
    // And, pass schema definitions for the primary keys of the source and
    // destination - we need to be explicit for our source, but the destination
    // class knows its schema already.
    $this->map = new MigrateSQLMap($this->machineName,
        array(
          'pastor' => array(
            'type' => 'varchar',
            'length' => 255,
            'not null' => TRUE,
            'description' => 'Pastor ID',
          ),
        ),
        MigrateDestinationTerm::getKeySchema()
      );

    // First, we set up a query for this data. Note that our source data
    // lives in a differnt database, on a connection defined in settings.php.  For this reason, we
    // use Database::getConnection instead of db_select, to specify the legacy DB as the DB to use.
    $query = Database::getConnection('default', 'mcrc_legacy')
      ->select('tblSermons', 's')
      ->fields('s', array('pastor'))
      ->groupBy('pastor');

    // Create a MigrateSource object, which manages retrieving the input data.
    $this->source = new MigrateSourceSQL($query);

    // Set up our destination - terms in the pastors vocabulary
    $this->destination = new MigrateDestinationTerm('pastors');

    // Mappings
    $this->addFieldMapping('name', 'pastor');
  }

  /**
   * Skip over duplicaate spellings of pastor names.  Also skip two in one.
   * @param $row
   * @return bool|void
   */
  public function prepareRow($row) {

    if ($row->pastor != $this->duplicatePastorCheck($row->pastor)) {
      return FALSE;
    }
  }
}