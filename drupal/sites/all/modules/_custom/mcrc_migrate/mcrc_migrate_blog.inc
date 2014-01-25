<?php
/**
 * @file
 * Migrate services into Drupal nodes.
 */

class MCRCBlogMigration extends MCRCMigrateBase {

  const PASTOR_SID_UID = 289;

  /**
   * Init the service migration.  Here we define the migration that will take records in the
   * Wordpress tables of the legacy database and create blog_post nodes.
   */
  function __construct() {
    parent::__construct();

    // Human-friendly description of migration process
    $this->description = t('Migrate blog posts as blog_post nodes.');

    // Create a map object for tracking the relationships between source rows
    // and their resulting Drupal objects. Pass the machine name
    // (MCRCBlog) of this migration to use in generating map and message tables.
    // And, pass schema definitions for the primary keys of the source and
    // destination - we need to be explicit for our source, but the destination
    // class knows its schema already.
    $this->map = new MigrateSQLMap($this->machineName,
        array(
          'ID' => array(
            'type' => 'int',
            'length' => 20,
            'not null' => TRUE,
            'description' => 'Post ID',
          ),
        ),
        MigrateDestinationNode::getKeySchema()
      );

    // First, we set up a query for this data. Note that our source data
    // lives in a differnt database, on a connection defined in settings.php.  For this reason, we
    // use Database::getConnection instead of db_select, to specify the legacy DB as the DB to use.
    $query = Database::getConnection('default', 'mcrc_legacy')
      ->select('wp_posts', 'p')
      ->fields('p', array('ID', 'post_date', 'post_content', 'post_title', 'post_excerpt', 'post_modified'))
      ->condition('post_type', 'post', '=')
      ->condition('post_status', 'publish', '=');

    // Create a MigrateSource object, which manages retrieving the input data.
    $this->source = new MigrateSourceSQL($query);

    // Set up our destination - terms in the pastors vocabulary
    $this->destination = new MigrateDestinationNode('blog_post');

    // Mappings
    $this->addFieldMapping('title', 'post_title');
    // Default the author to pastor sid, which we carefully pre-setup.
    $this->addFieldMapping('uid')
      ->defaultValue(self::PASTOR_SID_UID);
    $this->addFieldMapping('created', 'post_date');
    $this->addFieldMapping('changed', 'post_modified');
    $this->addFieldMapping('promote')
      ->defaultValue(1);

    // Body field
    $this->addFieldMapping('field_blog_post_body', 'post_content');
    $this->addFieldMapping('field_blog_post_body:format')
      ->defaultValue('wysiwyg');

  }

  /**
   * Tweak some things before continuing.
   * @param $row
   * @return bool|void
   */
  public function prepareRow($row) {

    // Adjust timestamps to UNIX timestamps.
    $row->post_date = strtotime($row->post_date);
    $row->post_modified = strtotime($row->post_modified);
  }
}