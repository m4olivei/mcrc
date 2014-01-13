<?php
/**
 * @file
 */

class MCRCUserMigration extends MCRCMigrateBase {

  /**
   * Init migration of users.
   */
  public function __construct() {
    parent::__construct();

    // Human-friendly description of migration process
    $this->description = t('Migrate users.');

    // Create a map object for tracking the relationships between source rows
    // and their resulting Drupal objects. Pass the machine name
    // (MCRCUser) of this migration to use in generating map and message tables.
    // And, pass schema definitions for the primary keys of the source and
    // destination - we need to be explicit for our source, but the destination
    // class knows its schema already.
    $this->map = new MigrateSQLMap($this->machineName,
        array(
          'userID' => array(
            'type' => 'int',
            'length' => 11,
            'not null' => TRUE,
            'description' => 'Service ID',
            'alias' => 'u',
          ),
        ),
        MigrateDestinationNode::getKeySchema()
      );

    // First, we set up a query for this data. Note that our source data
    // lives in a differnt database, on a connection defined in settings.php.  For this reason, we
    // use Database::getConnection instead of db_select, to specify the legacy DB as the DB to use.
    // @todo i've included a where clause to exclude in-Active users, do we want to bring them in for some reason?
    $query = Database::getConnection('default', 'mcrc_legacy')
      ->select('tblUsers', 'u')
      ->condition('u.Active', 1)
      ->fields('u', array('userID', 'FName', 'LName', 'eMailAddress', 'registeredDT', 'Active'))
      ->fields('s', array('firstLogin', 'isConfirmed'));
    $query->leftJoin('tblSystem', 's', 'u.systemID = s.systemID');
    $query->leftJoin('tblUsers_Publications', 'p', 'u.userID = p.userID');
    $query->groupBy('u.userID');
    $query->addExpression('GROUP_CONCAT(DISTINCT p.publicationID ORDER BY p.publicationID)', 'notifications');

    // Create a MigrateSource object, which manages retrieving the input data.
    $this->source = new MigrateSourceSQL($query);

    // Set up our destination - terms in the pastors vocabulary
    $this->destination = new MigrateDestinationUser();

    // Mappings
    $this->addFieldMapping('mail', 'eMailAddress');
    $this->addFieldMapping('name', 'eMailAddress');
    $this->addFieldMapping('roles')
      ->defaultValue(DRUPAL_AUTHENTICATED_RID);
    $this->addFieldMapping('status', 'Active');
    $this->addFieldMapping('created', 'registeredDT');
    $this->addFieldMapping('field_first_name', 'FName');
    $this->addFieldMapping('field_last_name', 'LName');
    $this->addFieldMapping('field_notifications', 'notifications');
  }

  /**
   * Process the incoming row for adjustments.  Skip inactive users on the old site.  Change the
   * date format on incoming date values.
   *
   * @param $row
   * @return bool|void
   */
  public function prepareRow($row) {
    // Convert to UNIX timestamp
    if ($row->registeredDT == '0000-00-00 00:00:00') {
      $row->registeredDT = strtotime('2008-01-01 00:00');
    }
    else {
      $row->registeredDT = strtotime($row->registeredDT);
    }

    if (!empty($row->notifications)) {
      $row->notifications = explode(',', $row->notifications);
    }
  }
}