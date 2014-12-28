<?php
/**
 * @file
 * Migrate Publications in as publication nodes.
 */

class MCRCPublicationsMigration extends MCRCMigrateBase {

  const LEGACY_BULLETIN = 1;
  const LEGACY_NEWSLETTER = 2;
  const LEGACY_CHURCH_FAMILY = 3;

  const V2_BULLETIN = 290;
  const V2_NEWSLETTER = 291;
  const V2_CHURCH_FAMILY = 292;
  const V2_NEIGHBORHOOD_LIST = 293;

  /**
   * Initiate the migration for Publications.
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

    // Store some mappings that we'll need from old to new
    $this->path_mappings = array(
      self::LEGACY_BULLETIN => '/publications/bulletin/',
      self::LEGACY_NEWSLETTER => '/publications/newsletter/',
      self::LEGACY_CHURCH_FAMILY => '/publications/churchfamily/',
    );
    $this->term_mapping = array(
      self::LEGACY_BULLETIN => self::V2_BULLETIN,
      self::LEGACY_NEWSLETTER => self::V2_NEWSLETTER,
      self::LEGACY_CHURCH_FAMILY => self::V2_CHURCH_FAMILY,
    );

    // Human-friendly description of migration process
    $this->description = t('Migrate publications.  Publications are access controlled.');

    // Create a map object for tracking the relationships between source rows
    // and their resulting Drupal objects. Pass the machine name
    // (MCRCPublicationsMigration) of this migration to use in generating map and message tables.
    // And, pass schema definitions for the primary keys of the source and
    // destination - we need to be explicit for our source, but the destination
    // class knows its schema already.
    $this->map = new MigrateSQLMap($this->machineName,
        array(
          'id' => array(
            'type' => 'int',
            'length' => 11,
            'not null' => TRUE,
            'description' => 'Publication ID',
          ),
        ),
        MigrateDestinationTerm::getKeySchema()
      );

    // First, we set up a query for this data. Note that our source data
    // lives in a differnt database, on a connection defined in settings.php.  For this reason, we
    // use Database::getConnection instead of db_select, to specify the legacy DB as the DB to use.
    $query = Database::getConnection('default', 'mcrc_legacy')
      ->select('tblPublications_Files', 'p');
    $query->addField('p', 'id');
    $query->addField('p', 'filename', 'date');
    $query->addField('p', 'filename', 'filename');
    $query->addField('p', 'publicationID');

    // Create a MigrateSource object, which manages retrieving the input data.
    $this->source = new MigrateSourceSQL($query);

    // Set up our destination - terms in the pastors vocabulary
    $this->destination = new MigrateDestinationNode('publication');

    // Mappings
    $this->addFieldMapping('field_publication_date', 'date');
    $this->addFieldMapping('field_publication_type', 'publicationID');
    $this->addFieldMapping('field_publication_type:source_type')
      ->defaultValue('tid');
    $this->addFieldMapping('field_publication_file', 'filename');
    $this->addFieldMapping('field_publication_file:file_replace')
      ->defaultValue(FILE_EXISTS_RENAME);
    $this->addFieldMapping('field_publication_file:preserve_files')
      ->defaultValue(TRUE);
  }

  /**
   * Skip over duplicaate spellings of pastor names.  Also skip two in one.
   * @param $row
   * @return bool|void
   */
  public function prepareRow($row) {

    $row->date = strtoupper(trim($row->date));
    if (preg_match('~^(\d{4}-\d{2}-\d{2})-?(AM|PM)?~', $row->date, $matches)) {
      $date = $matches[1];
      if (!empty($matches[2])) {
        $date .= ' ' . ($matches[2] == 'AM' ? '10:00' : '17:00');
      }
      else {
        $date .= ' 0:00';
      }
      $date .= ' UTC';
      $row->date = strtotime($date);
    }

    // Form the full path to the file
    $row->filename = 'http://legacy.mountainviewcrc.org' . $this->path_mappings[$row->publicationID] . $row->filename;

    // Convert the publicationID to the new tid
    $row->publicationID = $this->term_mapping[$row->publicationID];
  }
}