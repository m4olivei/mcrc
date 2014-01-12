/**
 * @file
 * A JavaScript file for the theme.
 * @todo use Drupal behaviors
 */
(function ($, Drupal, window, document, undefined) {

  /**
   * Our Drupal behavior that does all the magic.  This uses the module pattern which will run an
   * anonymous function that returns an object that is the public interface.  The attach key is returned
   * which is what Drupal will call anytime there are DOM updates.
   */
  Drupal.behaviors.wise = (function() {

    /**
     * Attach.  Returned to Drupal and called whenever the DOM changes.
     */
    function attach(context, settings) {
      _init_fitvids(context, settings);
      _init_menus(context, settings);
      _init_placeholderize(context, settings);
    }

    /**
     * Run fitvids on the content.
     * @private
     */
    function _init_fitvids(context, settings) {
      // Run fit vids on the main content area to ensure videos fit the area and adjust for responsive
      if ($.fn.fitVids && (typeof $.fn.fitVids == 'function')) {
        $('#content', context).fitVids();
      }
    }

    /**
     * Add interactivity to the mobile menus.
     * @private
     */
    function _init_menus() {

      if ($.fn.stackedNavigation && typeof $.fn.stackedNavigation == 'function') {
        $('.mobile-menu').stackedNavigation({menu_selector: '.menu-block-wrapper > ul.menu', title_selector: 'h2'});
      }
    }

    function _init_placeholderize(context, settings) {

      $('.view-filters', context).placeholderize();
      // Special case
      $.convertLabelToPlaceholder($('.views-widget-filter-date_filter label'), $('.views-widget-filter-date_filter input'));
    }

    // Return public interface
    return {
      attach: attach
    }
  })();

})(jQuery, Drupal, this, this.document);
