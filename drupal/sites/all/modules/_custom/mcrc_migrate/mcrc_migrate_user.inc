<?php
/**
 * @file
 */

class MCRCUserMigration extends MCRCMigrateBase {

  /**
   * Legacy role id constants
   */
  const MEMBER = 2;
  const ADMIN = 7616;
  const OFFICE_ADMIN = 7617;
  const VBS_ADMIN = 7618;
  const ELDER = 7619;
  const DEACON = 7620;
  const PMT = 7621;
  const MLT = 7622;
  const GEMS = 7623;

  /**
   * New role id constants
   */
  const MCRC_DRUAPL_MEMBER = 12;
  const MCRC_DRUPAL_SITE_ADMIN = 4;
  const MCRC_DRUPAL_CONTENT_ADMIN = 3;
  const MCRC_DRUPAL_VBS_ADMIN = 6;
  const MCRC_DRUPAL_ELDER = 7;
  const MCRC_DRUPAL_DEACON = 8;
  const MCRC_DRUPAL_PMT = 9;
  const MCRC_DRUPAL_MLT = 10;
  const MCRC_DRUPAL_GEMS = 11;

  /**
   * Init migration of users.
   */
  public function __construct() {
    parent::__construct();
    
    // Create a map of old to new rols
    $this->role_map = array(
      self::MEMBER => self::MCRC_DRUAPL_MEMBER,
      self::ADMIN => self::MCRC_DRUPAL_SITE_ADMIN,
      self::OFFICE_ADMIN => self::MCRC_DRUPAL_CONTENT_ADMIN,
      self::VBS_ADMIN => self::MCRC_DRUPAL_VBS_ADMIN,
      self::ELDER => self::MCRC_DRUPAL_ELDER,
      self::DEACON => self::MCRC_DRUPAL_DEACON,
      self::PMT => self::MCRC_DRUPAL_PMT,
      self::MLT => self::MCRC_DRUPAL_MLT,
      self::GEMS => self::MCRC_DRUPAL_GEMS,
    );

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
    $query = Database::getConnection('default', 'mcrc_legacy')
      ->select('tblUsers', 'u')
      ->condition('u.Active', 1)
      ->fields('u', array('userID', 'FName', 'LName', 'eMailAddress', 'registeredDT', 'Active'))
      ->fields('s', array('firstLogin', 'isConfirmed'));
    $query->leftJoin('tblSystem', 's', 'u.systemID = s.systemID');
    $query->leftJoin('tblUsers_Publications', 'p', 'u.userID = p.userID');
    $query->leftJoin('tblUsers_Roles', 'ur', 'u.userID = ur.userID');
    $query->groupBy('u.userID');
    $query->addExpression('GROUP_CONCAT(DISTINCT p.publicationID ORDER BY p.publicationID)', 'notifications');
    $query->addExpression('GROUP_CONCAT(DISTINCT ur.roleID ORDER BY ur.roleID)', 'roles');

    // Create a MigrateSource object, which manages retrieving the input data.
    $this->source = new MigrateSourceSQL($query);

    // Set up our destination - terms in the pastors vocabulary
    $this->destination = new MigrateDestinationUser();

    // Mappings
    $this->addFieldMapping('mail', 'eMailAddress');
    $this->addFieldMapping('name', 'eMailAddress');
    $this->addFieldMapping('roles', 'roles')
      ->defaultValue(DRUPAL_AUTHENTICATED_RID);
    $this->addFieldMapping('status', 'Active');
    $this->addFieldMapping('created', 'registeredDT');
    $this->addFieldMapping('field_first_name', 'FName');
    $this->addFieldMapping('field_last_name', 'LName');
    $this->addFieldMapping('field_notifications', 'notifications')
      ->separator(',');
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

    // Make sure the roles coming in are ligit and are mapped to new role numbers
    $legacy_roles = array_keys($this->role_map);
    if (!empty($row->roles)) {
      $new_roles = array(DRUPAL_AUTHENTICATED_RID);
      $row->roles = explode(',', $row->roles);

      foreach ($row->roles as $role) {
        if (in_array($role, $legacy_roles)) {
          $new_roles[] = $this->role_map[$role];
        }
      }
      $row->roles = $new_roles;
    }
  }
}