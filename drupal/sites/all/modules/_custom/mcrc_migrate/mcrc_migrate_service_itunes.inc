<?php
/**
 * @file
 * Migrate services into Drupal nodes from the new iTunes feed.
 */

class MCRCServiceItunesMigration extends XMLMigration {

  /**
   * Init the service migration.  Here we define the migration that will take records in the
   * tblSermons table of the legacy database and create service nodes.
   */
  function __construct() {
    parent::__construct();

    // Human-friendly description of migration process
    $this->description = t('Migrate services as service nodes from the new iTunes feed.');

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
          'guid' => array(
            'type' => 'varchar',
            'length' => 128,
            'not null' => TRUE,
            'description' => 'Guid',
          ),
        ),
        MigrateDestinationNode::getKeySchema()
      );

    // Setup the source of the migration, which is the XML iTunes feed.

    // There isn't a consistent way to automatically identify appropriate "fields"
    // from an XML feed, so we pass an explicit list of source fields.
    $fields = array(
      'title' => t('Title'),
      'description' => t('Description'),
      'pubDate' => t('Created date'),
      'guid' => t('Unique identifier, also the URL to the MP3 file.'),
    );

    // Prepare the parameters to MigrateItemsXML
    $items_url = 'http://www.buzzsprout.com/16693.rss';
    // Relative to the document.
    $item_xpath = '/rss/channel/item';
    // Relative to item_xpath and gets assembled.
    $item_ID_xpath = 'guid';

    $items_class  = new MigrateItemsXML($items_url, $item_xpath, $item_ID_xpath);
    $this->source = new MigrateSourceMultiItems($items_class, $fields);

    // Set up our destination - terms in the pastors vocabulary
    $this->destination = new MigrateDestinationNode('service');

    // Mappings
    $this->addFieldMapping('title', 'title')->xpath('title');
    $this->addFieldMapping('uid')
      ->defaultValue(1);
    $this->addFieldMapping('created', 'pubDate')->xpath('pubDate');
    $this->addFieldMapping('changed', 'pubDate')->xpath('pubDate');
    $this->addFieldMapping('promote')
      ->defaultValue(1);

    // NOTE: for this date field to migrate properly, need to have Date Migration module on.
    $this->addFieldMapping('field_service_date', 'pubDate')->xpath('pubDate');
    // We'll need to process this in prepareRow to form the correct URL.
    // @see https://drupal.org/node/1540106
    $this->addFieldMapping('field_service_audio', 'guid')->xpath('guid');
    // These settings makes it so that files are only migrated once, no need to do it every time we rollback.
    // It just works, which is awesome.  If the file isn't there, it's downloaded according to the file field settings
    // and an entry is created in the file_managed table.
    $this->addFieldMapping('field_service_audio:file_replace')
      ->defaultValue(MigrateFile::FILE_EXISTS_REUSE);
    $this->addFieldMapping('field_service_audio:preserve_files')
      ->defaultValue(TRUE);
    $this->addFieldMapping('body', 'description')->xpath('description');
    $this->addFieldMapping('body:format')
      ->defaultValue('wysiwyg');
  }

  /**
   * Tweak some things before continuing.
   * @param $row
   * @return bool|void
   */
  public function prepareRow($row) {

    $row->pubDate = strtotime(current($row->xml->xpath('pubDate')));
  }
}