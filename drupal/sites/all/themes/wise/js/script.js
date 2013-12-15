/**
 * @file
 * A JavaScript file for the theme.
 * @todo use Drupal behaviors
 */
(function ($, Drupal, window, document, undefined) {

  $(document).ready(function() {

    // Run fit vids on the main content area to ensure videos fit the area and adjust for responsive
    if ($.fn.fitVids && (typeof $.fn.fitVids == 'function')) {
      $('#content').fitVids();
    }
  });

})(jQuery, Drupal, this, this.document);
