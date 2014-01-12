/**
 * placeholderize.js
 *
 * Take form labels and stuff them in inputs as placeholders.
 *
 * @param options
 *
 * @todo Put this in base theme. Possibly make a repo for this.
 */

(function($) {
  $.fn.placeholderize = function(options) {
    var defaults = {}
      , options  = $.extend(defaults, options);

    // Don't run this plugin if the browser does not support placeholders.
    if (!browserSupportsPlaceholders()) {
      return;
    }

    this.each(function() {
      var $form = $(this);
      convertLabelsToPlaceholders($form);
    });
  };

  /**
   * Traverses a form and converts labels to placeholders.
   *
   * @param $form Object
   */
  function convertLabelsToPlaceholders($form) {
    $form.find('label').each(function() {
      var $label  = $(this)
        , id      = $label.attr('for')
        , $input  = (id) ? $('#' + id) : null;

      if ($input) {
        $.convertLabelToPlaceholder($label, $input);
      }
    });
  };

  /**
   * Takes the text from a label and puts it into a placeholder.
   *
   * @param $label Object
   * @param $input Object
   */
  $.convertLabelToPlaceholder = function ($label, $input) {
    var text = $.trim($label.text());

    // Do not convert the label if the input doesn't support placeholders.
    if (text && elementSupportsPlaceholder($input)) {
      $input.attr('placeholder', text);
      $label.addClass('element-invisible'); // A class for an accessible way to hide the element.
    }
  };

  /**
   * Test if placeholder is supported by the browser.
   *
   * @return Boolean true if supported.
   */
  function browserSupportsPlaceholders() {
    return ('placeholder' in document.createElement('input'));
  };

  /**
   * Test if placeholder is supported by the element.
   *
   * @param $input Object
   * @return Boolean true if supported.
   */
  function elementSupportsPlaceholder($el) {
    var blacklist = ['checkbox', 'radio', 'button', 'submit', 'reset', 'file'];

    return (($el.is('input') || $el.is('textarea')) && blacklist.indexOf($el.attr('type')) < 0);
  };
})(jQuery);