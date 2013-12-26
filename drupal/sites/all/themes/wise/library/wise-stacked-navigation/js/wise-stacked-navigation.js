/**
 * Stacked navigation enhancement
 *
 * @todo for accessibility, wrap the outer h2 with a link, and add text to say 'Hide/Show'
 * @todo refactor the expand/collapse stuff into custom events that get triggered ala DWPE
 * @todo toggle the .toggle-status to Show/Hide
 *
 * @param options
 */
(function($) {
  $.fn.stackedNavigation = function(options) {
    var defaults = {
        menu_selector: '',
        title_selector: ''
      },
      options = $.extend(defaults, options);



    // Apply class=has-children on those items with children
    this.each(function() {
      var $title,
        $menu;

      if (options.menu_selector) {
        $menu = $(options.menu_selector, this);
      }
      else {
        $menu = $(this);
      }

      if (options.title_selector) {
        $title = $(options.title_selector, this);
      }
      else {
        $title = $menu.siblings('h2');
      }

      $menu.find('li').each(function() {
        var $this = $(this),
          anchor = $this.find('> a');

        if ($this.find('ul').length > 0) {
          $this.addClass('has-children');
          $this.find('ul').addClass('closed').attr('aria-hidden', true);
          anchor.before('<a href="#" class="nav-toggle"><span class="toggle-status">Show</span> ' + anchor.html() + ' Submenu</a>');
        }
      });

      // Make the h2 toggle the whole menu
      $menu.addClass('closed');
      $title.addClass('nav-toggle nav-toggle-closed').click(function() {
        if ($menu.hasClass('closed')) {
          // Was closed, so open it
          $title
            .removeClass('nav-toggle-closed')
            .addClass('nav-toggle-open');
        }

        $menu
          .slideToggle(function() {

            if ($menu.hasClass('closed')) {
              // Was closed, so open it
              $menu
                .removeClass('closed')
                .removeAttr('aria-hidden')
                .addClass('open');
            }
            else {
              // Was open so close it
              $menu
                .removeClass('open')
                .addClass('closed')
                .attr('aria-hidden', 'true');
              $title
                .removeClass('nav-toggle-open')
                .addClass('nav-toggle-closed');
            }
            $menu.removeAttr('style');
          });
      });
    });

    // Click event for the toggle links
    $(document).delegate('a.nav-toggle', 'click', function() {

      // Expand the clicked one
      $(this).parent().children('ul').slideToggle('fast', function() {
        var $this = $(this);

        if ($this.hasClass('closed')) {
          // Was closed, so open it
          $this.removeClass('closed');
          $this.removeAttr('aria-hidden');
          $this.addClass('open');
        }
        else {
          // Was open so close it
          $this.removeClass('open');
          $this.addClass('closed');
          $this.attr('aria-hidden', 'true');
        }
        $this.removeAttr('style');
      }); // end slideToggle

      // Toggle a class on the parent li
      $(this).parent().toggleClass('nav-expanded');

      // Collapse other open ul's at the same level
      $(this).parent().siblings().find('ul.open').slideToggle('fast', function() {
        var $this = $(this);

        // Was open so close it
        $this.removeClass('open');
        $this.addClass('closed');
        $this.attr('aria-hidden', 'true');

        $this.removeAttr('style');
      }).each(function() {
          $(this).parent().toggleClass('nav-expanded');
        });

      // Prevent default browser behavior
      return false;
    });
  }
})(jQuery);