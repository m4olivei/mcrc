<?php
/**
 * @file
 * Common base class for our migrations.   Take care of all the common stuff and implement
 * helper functions.
 */

class MCRCMigrateBase extends DynamicMigration {

  /**
   * Just pass things along to the parent class.
   */
  public function __construct() {
    parent::__construct();
  }

  /**
   * Map incorrect spellings of pastors that are coming in to their correct version
   * to void duplicates.
   *
   * @param $name
   *  Name of the pastor being imported.
   */
  protected function duplicatePastorCheck($name) {
    $map = array(
      'Pastor André Basson' => 'Pastor André Basson',
      'Dr. Andre Basson' => 'Pastor André Basson',
      'Dr. A. Basson' => 'Pastor André Basson',
      'Dr. Andr&#233; Basson' => 'Pastor André Basson',
      'Dr. Andre Basson' => 'Pastor André Basson',
      'Pastor Andre Basson' => 'Pastor André Basson',

      'Dr. J. Payton' => 'Dr. James Payton',

      'Missionary John Span' => 'John Span',

      'Mr Wes Collins' => 'Pastor Wes Collins',
      'Mr. Wes Collins' => 'Pastor Wes Collins',

      'Pastor Dave Tigchelaar' => 'Pastor David Tigchelaar',
      'Pastor David Tighelaar' => 'Pastor David Tigchelaar',
      'Pastor David Tihchelaar' => 'Pastor David Tigchelaar',

      'Pastor E.J. deWaard' => 'Pastor EJ de Waard',

      'Pastor H. VanderWindt' => 'Pastor Harry VanderWindt',

      'Pastor J.J. Hoytema' => 'Pastor Jerry Hoytema',
      'Pastor Jerry J Hoytema' => 'Pastor Jerry Hoytema',
      'Pastor Jerry J. Hoytema' => 'Pastor Jerry Hoytema',

      'Pastor Michael Collins' => 'Pastor Mike Collins',
      'Pastor Micheal Collins' => 'Pastor Mike Collins',

      'Pastor Peter Breedveld' => 'Pastor Peter Breedveld Sr.',
      'Pastor Peter Breeveld Sr.' => 'Pastor Peter Breedveld Sr.',

      'Pastor Steve de Boer' => 'Pastor Steve deBoer',
      'Pastor Steven deBoer' => 'Pastor Steve deBoer',

      'Rev. Fred Vanderberg' => 'Pastor Fred VanderBerg',

      'Rev. J.W. Van Weelden' => 'Rev. J.M. VanWeelden',

      'Pastors R. Roeda &amp; K. Stieva' => 'Pastor Rick Roeda',

      'Pastor Steve deBoer &amp; J.W. VanWeelden' => 'Pastor Steve deBoer',

      'Pastor Jim Dekker & Pastor Chris Winter' => 'Pastor Jim Dekker',

      'Pastor Kevin Stieva &amp; Bruce Adema' => 'Rev. Bruce Adema',
    );

    return isset($map[$name]) ? $map[$name] : $name;
  }
}