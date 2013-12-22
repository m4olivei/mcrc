/**
 * @file
 * Init the flexslider jQuery plugin
 * @todo add control for video
 */
(function ($, Drupal, window, document, undefined) {

  Drupal.behaviors.wiseSlider = (function() {

    function attach(context, settings) {

    }

    function init() {

      $(window).load(load);
    }

    function load() {

      // Call fitVid before FlexSlider initializes, so the proper initial height can be retrieved.
      if ($.fn.fitVids && (typeof $.fn.fitVids == 'function')) {
        $('.flexslider').fitVids();
      }

      if ($.fn.flexslider && (typeof $.fn.flexslider == 'function')) {
        $('.flexslider')
          .flexslider({
            animation: 'fade',
            useCSS: false,
            animationLoop: true,
            smoothHeight: false,
            video: true,
            prevText: '<i class="icon-caret-left"></i>',
            nextText: '<i class="icon-caret-right"></i>'
          });
      }
    }

    // Return public interface
    return {
      attach: attach,
      init: init
    }
  })();

  // Kick things off
  Drupal.behaviors.wiseSlider.init();
})(jQuery, Drupal, this, this.document);
