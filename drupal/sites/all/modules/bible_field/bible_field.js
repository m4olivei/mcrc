/**
 * @file
 * Shell for Javascript functionality for future.
 */
(function($) {

  /**
   * Our Drupal behavior that does all the magic.  This uses the module pattern which will run an
   * anonymous function that returns an object that is the public interface.  The attach key is returned
   * which is what Drupal will call anytime there are DOM updates.
   */
  Drupal.behaviors.bibleField = (function() {

    /**
     * Attach.  Returned to Drupal and called whenever the DOM changes.
     */
    function attach(context, settings) {

    }

    // Return public interface
    return {
      attach: attach
    }
  })();
})(jQuery);
