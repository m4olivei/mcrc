<?php
/**
 * @file
 * Migrate services into Drupal nodes.
 */

class MCRCServiceMigration extends MCRCMigrateBase {

  /**
   * Init the service migration.  Here we define the migration that will take records in the
   * tblSermons table of the legacy database and create service nodes.
   */
  function __construct() {
    parent::__construct();

    // Human-friendly description of migration process
    $this->description = t('Migrate services as service nodes.');

    // Declare dependencies for our migration - other migrations
    // which should run first. In this case, terms assigned to our nodes
    // should be migrated before the nodes themselves.
    $this->dependencies = array('MCRCPastorTerm');

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
    $this->addFieldMapping('uid')
      ->defaultValue(1);
    $this->addFieldMapping('created', 'date_uploaded');
    $this->addFieldMapping('changed', 'date_uploaded');
    $this->addFieldMapping('promote')
      ->defaultValue(1);

    $this->addFieldMapping('field_service_date', 'date_presented');
    // We'll need to process this in prepareRow to form the correct URL.
    $this->addFieldMapping('field_service_audio', 'filename');
    $this->addFieldMapping('field_service_audio:file_replace')
      ->defaultValue(MigrateFile::FILE_EXISTS_REUSE);
    $this->addFieldMapping('field_service_audio:preserve_files')
      ->defaultValue(TRUE);

    // We'll process this mapping in prepareRow to swap for the correct spelling of the pastor name.
    $this->addFieldMapping('field_service_pastor', 'pastor');
  }

  /**
   * Tweak some things before continuing.
   * @param $row
   * @return bool|void
   */
  public function prepareRow($row) {

    // Adjust timestamps to UNIX timestamps, some early sermons don't have a value for date_uploaded.
    // In that case, set to date_presented.
    $row->date_presented = strtotime($row->date_presented);
    if ($row->date_uploaded) {
      $row->date_uploaded = strtotime($row->date_uploaded);
    }
    else if ($row->date_presented) {
      $row->date_uploaded = $row->date_presented;
    }

    // Form a valid URL to the audio file.
    $row->filename = 'http://mountainviewcrc.org/listentothemessage/messages/' . $row->filename;

    // Check the pastor spelling to get the common spelling of this pastor.
    $row->pastor = $this->duplicatePastorCheck($row->pastor);
  }
}