<?php
/**
 * @file
 * Standard theme overrides that sub in Twitter Bootstrap classing or otherwise do stuff that all themes need
 *
 * @todo documentation
 * @todo login/logout/my account link depending on context
 * @todo responsive drop down menus
 * @todo add Twitter bootstrap classing to webform elements
 */

/***********************************************************************************************************************
 * =Theme overrides and preprocessors
 **********************************************************************************************************************/


/**
 * Override theme_menu_local_tasks to change the classing on the <ul> to use Twitter Bootstrap Navs
 *
 * @param $variables
 * @return string
 */
function wise_menu_local_tasks(&$variables) {
  $output = '';

  if (!empty($variables['primary'])) {
    $variables['primary']['#prefix'] = '<h2 class="element-invisible">' . t('Primary tabs') . '</h2>';
    $variables['primary']['#prefix'] .= '<ul class="nav nav-tabs primary">';
    $variables['primary']['#suffix'] = '</ul>';
    $output .= drupal_render($variables['primary']);
  }
  if (!empty($variables['secondary'])) {
    $variables['secondary']['#prefix'] = '<h2 class="element-invisible">' . t('Secondary tabs') . '</h2>';
    $variables['secondary']['#prefix'] .= '<ul class="nav nav-pills secondary">';
    $variables['secondary']['#suffix'] = '</ul>';
    $output .= drupal_render($variables['secondary']);
  }

  return $output;
}

/**
 * Override theme_status_messages to change the classing to the wrapper to use Twitter Bootstrap alerts.
 *
 * @param $variables
 * @return string
 */
function wise_status_messages($variables) {
  $display = $variables['display'];
  $output = '';

  $status_heading = array(
    'status' => t('Status message'),
    'error' => t('Error message'),
    'warning' => t('Warning message'),
    'info' => t('Information message'),
  );
  $twitter_class = array(
    'status' => 'alert-success',
    'error' => 'alert-error',
    'warning' => 'alert-block',
    'info' => 'alert-info',
  );
  foreach (drupal_get_messages($display) as $type => $messages) {

    $output .= '<div class="alert ' . $twitter_class[$type] . '">' . "\n";
    if (!empty($status_heading[$type])) {
      $output .= '<h2 class="element-invisible">' . $status_heading[$type] . "</h2>\n";
    }
    if (count($messages) > 1) {
      $output .= " <ul>\n";
      foreach ($messages as $message) {
        $output .= '  <li>' . $message . "</li>\n";
      }
      $output .= " </ul>\n";
    }
    else {
      $output .= $messages[0];
    }
    $output .= "</div>\n";
  }
  return $output;
}

/**
 * Overrides theme_pager() to change the classing to use Twitter Bootstrap pagination.
 * Adapted from BH Bootstrap theme.
 *
 * @param $variables
 * @return string
 * @see http://drupalcode.org/project/bh_bootstrap.git/commit/d13f070
 */
function wise_pager($variables) {
  $tags = $variables['tags'];
  $element = $variables['element'];
  $parameters = $variables['parameters'];
  $quantity = $variables['quantity'];
  global $pager_page_array, $pager_total;

  // Calculate various markers within this pager piece:
  // Middle is used to "center" pages around the current page.
  $pager_middle = ceil($quantity / 2);
  // current is the page we are currently paged to
  $pager_current = $pager_page_array[$element] + 1;
  // first is the first page listed by this pager piece (re quantity)
  $pager_first = $pager_current - $pager_middle + 1;
  // last is the last page listed by this pager piece (re quantity)
  $pager_last = $pager_current + $quantity - $pager_middle;
  // max is the maximum page number
  $pager_max = $pager_total[$element];
  // End of marker calculations.

  // Prepare for generation loop.
  $i = $pager_first;
  if ($pager_last > $pager_max) {
    // Adjust "center" if at end of query.
    $i = $i + ($pager_max - $pager_last);
    $pager_last = $pager_max;
  }
  if ($i <= 0) {
    // Adjust "center" if at start of query.
    $pager_last = $pager_last + (1 - $i);
    $i = 1;
  }
  // End of generation loop preparation.
  $li_first = theme('pager_first', array('text' => t('First'), 'element' => $element, 'parameters' => $parameters));
  $li_previous = theme('pager_previous', array('text' => t('Previous'), 'element' => $element, 'interval' => 1, 'parameters' => $parameters));
  $li_next = theme('pager_next', array('text' => t('Next'), 'element' => $element, 'interval' => 1, 'parameters' => $parameters));
  $li_last = theme('pager_last', array('text' => t('Last'), 'element' => $element, 'parameters' => $parameters));

  if ($pager_total[$element] > 1) {
    if ($li_first) {
      $items[] = array(
        'class' => array('pager-first'),
        'data' => $li_first,
      );
    }
    if ($li_previous) {
      $items[] = array(
        'class' => array('pager-previous'),
        'data' => $li_previous,
      );
    }

    // When there is more than one page, create the pager list.
    if ($i != $pager_max) {
      if ($i > 1) {
        $items[] = array(
          'class' => array('pager-ellipsis', 'disabled'),
          'data' => '<a href="#">…</a>',
        );
      }
      // Now generate the actual pager piece.
      for (; $i <= $pager_last && $i <= $pager_max; $i++) {
        if ($i < $pager_current) {
          $items[] = array(
            //'class' => array('pager-item'),
            'data' => theme('pager_previous', array('text' => $i, 'element' => $element, 'interval' => ($pager_current - $i), 'parameters' => $parameters)),
          );
        }
        if ($i == $pager_current) {
          $items[] = array(
            'class' => array('pager-current', 'disabled'),
            'data' => '<a href="#">' . $i . '</a>',
          );
        }
        if ($i > $pager_current) {
          $items[] = array(
            //'class' => array('pager-item'),
           'data' => theme('pager_next', array('text' => $i, 'element' => $element, 'interval' => ($i - $pager_current), 'parameters' => $parameters)),
          );
        }
      }
      if ($i < $pager_max) {
        $items[] = array(
          'class' => array('pager-ellipsis', 'disabled'),
          'data' => '<a href="#">…</a>',
        );
      }
    }
    // End generation.
    if ($li_next) {
      $items[] = array(
        'class' => array('pager-next'),
        'data' => $li_next,
      );
    }
    if ($li_last) {
      $items[] = array(
         'class' => array('pager-last'),
        'data' => $li_last,
      );
    }
      return '<h2 class="element-invisible">' . t('Pages') . '</h2>' . '<div class="' . implode(' ', array_map('check_plain', theme_get_setting('wise_pager__classes'))) . '">' . theme('item_list', array(
        'items' => $items,
      //'attributes' => array('class' => array('pagination')),
    )) . '</div>';
  }
} // wise_pager()

/**
 * Override theme_views_mini_pager() to add Bootstrap classing.
 *
 * @param $vars
 * @return string
 */
function wise_views_mini_pager($vars) {
  global $pager_page_array, $pager_total;

  $tags = $vars['tags'];
  $element = $vars['element'];
  $parameters = $vars['parameters'];
  $quantity = $vars['quantity'];

  // Calculate various markers within this pager piece:
  // Middle is used to "center" pages around the current page.
  $pager_middle = ceil($quantity / 2);
  // current is the page we are currently paged to
  $pager_current = $pager_page_array[$element] + 1;
  // max is the maximum page number
  $pager_max = $pager_total[$element];
  // End of marker calculations.



  if ($pager_total[$element] > 1) {

    $li_previous = theme('pager_previous',
      array(
        'text' => (isset($tags[1]) ? $tags[1] : t('‹‹')),
        'element' => $element,
        'interval' => 1,
        'parameters' => $parameters,
      )
    );
    if (empty($li_previous)) {
      $li_previous = "&nbsp;";
    }

    $li_next = theme('pager_next',
      array(
        'text' => (isset($tags[3]) ? $tags[3] : t('››')),
        'element' => $element,
        'interval' => 1,
        'parameters' => $parameters,
      )
    );

    if (empty($li_next)) {
      $li_next = "&nbsp;";
    }

    $items[] = array(
      'class' => array('pager-previous'),
      'data' => $li_previous,
    );

    $items[] = array(
      'data' => '<span>' . t('@current of @max', array('@current' => $pager_current, '@max' => $pager_max)) . '</span>',
    );

    $items[] = array(
      'class' => array('pager-next'),
      'data' => $li_next,
    );
    return '<div class="pagination pagination-centered">' . theme('item_list',
      array(
        'items' => $items,
        'title' => NULL,
        'type' => 'ul',
      )
    ) . '</div>';
  }
}

/**
 * Override theme_breadcrumb(). Return a themed breadcrumb trail.
 *
 * @param $variables
 *   - title: An optional string to be used as a navigational heading to give
 *     context for breadcrumb links to screen-reader users.
 *   - title_attributes_array: Array of HTML attributes for the title. It is
 *     flattened into a string within the theme function.
 *   - breadcrumb: An array containing the breadcrumb links.
 * @return
 *   A string containing the breadcrumb output.
 */
function wise_breadcrumb($variables) {
  $breadcrumb = $variables['breadcrumb'];
  $output = '';

  // Determine if we are to display the breadcrumb.
  $show_breadcrumb = theme_get_setting('zen_breadcrumb');
  if ($show_breadcrumb == 'yes' || $show_breadcrumb == 'admin' && arg(0) == 'admin') {

    // Optionally get rid of the homepage link.
    $show_breadcrumb_home = theme_get_setting('zen_breadcrumb_home');
    if (!$show_breadcrumb_home) {
      array_shift($breadcrumb);
    }

    // Return the breadcrumb with separators.
    if (!empty($breadcrumb)) {
      $breadcrumb_separator = '<span class="divider">' . theme_get_setting('zen_breadcrumb_separator') . '</span>';
      $trailing_separator = $title = '';
      if (theme_get_setting('zen_breadcrumb_title')) {
        $item = menu_get_item();
        if (!empty($item['tab_parent'])) {
          // If we are on a non-default tab, use the tab's title.
          $breadcrumb[] = check_plain($item['title']);
        }
        else {
          $breadcrumb[] = drupal_get_title();
        }
      }
      elseif (theme_get_setting('zen_breadcrumb_trailing')) {
        $trailing_separator = $breadcrumb_separator;
      }

      // Provide a navigational heading to give context for breadcrumb links to
      // screen-reader users.
      if (empty($variables['title'])) {
        $variables['title'] = t('You are here');
      }
      // Unless overridden by a preprocess function, make the heading invisible.
      if (!isset($variables['title_attributes_array']['class'])) {
        $variables['title_attributes_array']['class'][] = 'element-invisible';
      }

      // Build the breadcrumb trail.
      $output = '<nav id="breadcrumb" role="navigation">';
      $output .= '<h2' . drupal_attributes($variables['title_attributes_array']) . '>' . $variables['title'] . '</h2>';
      $output .= '<ul class="breadcrumb"><li>' . implode($breadcrumb_separator . '</li><li>', $breadcrumb) . $trailing_separator . '</li></ul>';
      $output .= '</nav>';
    }
  }

  return $output;
}

/**
 * Overrides theme_menu_tree() for menu blocks configured for a navbar list style
 * (requires wise_tweaks module)
 */
function wise_menu_tree__menu_block__navbar($variables) {
  return '<ul class="nav">' . $variables['tree'] . '</ul>';
}

/**
 * Overrides theme_menu_tree() for menu blocks configured for a nav-list list style
 * (requires wise_tweaks module)
 */
function wise_menu_tree__menu_block__nav_list($variables) {
  return '<ul class="nav nav-list">' . $variables['tree'] . '</ul>';
}

/**
 * Overrides theme_webform_element().
 */
function wise_webform_element($variables) {
  // Ensure defaults.
  $variables['element'] += array(
    '#title_display' => 'before',
  );

  $element = $variables['element'];

  // All elements using this for display only are given the "display" type.
  if (isset($element['#format']) && $element['#format'] == 'html') {
    $type = 'display';
  }
  else {
    $type = (isset($element['#type']) && !in_array($element['#type'], array('markup', 'textfield', 'webform_email', 'webform_number'))) ? $element['#type'] : $element['#webform_component']['type'];
  }

  // Convert the parents array into a string, excluding the "submitted" wrapper.
  $nested_level = $element['#parents'][0] == 'submitted' ? 1 : 0;
  $parents = str_replace('_', '-', implode('--', array_slice($element['#parents'], $nested_level)));

  $wrapper_classes = array(
   'form-item',
   'webform-component',
   'webform-component-' . $type,
   'control-group',
  );
  // Check for errors and set correct error class
  if (isset($element['#parents']) && form_get_error($element)) {
    $wrapper_classes[] = 'error';
  }
  if (isset($element['#title_display']) && strcmp($element['#title_display'], 'inline') === 0) {
    $wrapper_classes[] = 'webform-container-inline';
  }
  $output = '<div class="' . implode(' ', $wrapper_classes) . '" id="webform-component-' . $parents . '">' . "\n";

  // If #title is not set, we don't display any label or required marker.
  if (!isset($element['#title'])) {
    $element['#title_display'] = 'none';
  }
  $prefix = isset($element['#field_prefix']) ? '<span class="field-prefix">' . _webform_filter_xss($element['#field_prefix']) . '</span> ' : '';
  $suffix = isset($element['#field_suffix']) ? ' <span class="field-suffix">' . _webform_filter_xss($element['#field_suffix']) . '</span>' : '';

  switch ($element['#title_display']) {
    case 'inline':
    case 'before':
    case 'invisible':
      $output .= ' ' . theme('form_element_label', $variables);
      $output .= ' ' . $prefix . $element['#children'] . $suffix . "\n";
      break;

    case 'after':
      $output .= ' ' . $prefix . $element['#children'] . $suffix;
      $output .= ' ' . theme('form_element_label', $variables) . "\n";
      break;

    case 'none':
    case 'attribute':
      // Output no label and no required marker, only the children.
      $output .= ' ' . $prefix . $element['#children'] . $suffix . "\n";
      break;
  }

  if (!empty($element['#description'])) {
    $output .= ' <div class="description">' . $element['#description'] . "</div>\n";
  }

  $output .= "</div>\n";

  return $output;
}

/***********************************************************************************************************************
 * =Borrowed from the Twitter Bootstrap Drupal Theme http://drupal.org/project/bootstrap
 **********************************************************************************************************************/
/**
 * Overrides theme_form_element().  Returns HTML for a form element.
 *
 * Changes some of the classes and markup to match Twitter Bootstraps classing.
 *
 * Taken from d.o/project/bootstrap
 */
function wise_form_element(&$variables) {
  $element = &$variables['element'];
  // This is also used in the installer, pre-database setup.
  $t = get_t();

  // This function is invoked as theme wrapper, but the rendered form element
  // may not necessarily have been processed by form_builder().
  $element += array(
    '#title_display' => 'before',
  );

  // Add element #id for #type 'item'.
  if (isset($element['#markup']) && !empty($element['#id'])) {
    $attributes['id'] = $element['#id'];
  }

  // Add bootstrap class
  $attributes['class'] = array('control-group');

  // Check for errors and set correct error class
  if (isset($element['#parents']) && form_get_error($element)) {
    $attributes['class'][] = 'error';
  }

  if (!empty($element['#type'])) {
    $attributes['class'][] = 'form-type-' . strtr($element['#type'], '_', '-');
  }
  if (!empty($element['#name'])) {
    $attributes['class'][] = 'form-item-' . strtr($element['#name'], array(' ' => '-', '_' => '-', '[' => '-', ']' => ''));
  }
  // Add a class for disabled elements to facilitate cross-browser styling.
  if (!empty($element['#attributes']['disabled'])) {
    $attributes['class'][] = 'form-disabled';
  }
  $output = '<div' . drupal_attributes($attributes) . '>' . "\n";

  // If #title is not set, we don't display any label or required marker.
  if (!isset($element['#title'])) {
    $element['#title_display'] = 'none';
  }
  $prefix = isset($element['#field_prefix']) ? '<span class="field-prefix">' . $element['#field_prefix'] . '</span> ' : '';
  $suffix = isset($element['#field_suffix']) ? ' <span class="field-suffix">' . $element['#field_suffix'] . '</span>' : '';

  switch ($element['#title_display']) {
    case 'before':
    case 'invisible':
      $output .= ' ' . theme('form_element_label', $variables);
      $output .= '<div class="controls">';
      $output .= ' ' . $prefix . $element['#children'] . $suffix . "\n";
      break;

    case 'after':
      $output .= '<div class="controls">';
      $variables['#children'] = ' ' . $prefix . $element['#children'] . $suffix;
      $output .= ' ' . theme('form_element_label', $variables) . "\n";
      break;

    case 'none':
    case 'attribute':
      // Output no label and no required marker, only the children.
      $output .= '<div class="controls">';
      $output .= ' ' . $prefix . $element['#children'] . $suffix . "\n";
      break;
  }

  if ( !empty($element['#description']) ) {
    $output .= '<p class="help-block">' . $element['#description'] . "</p>\n";
  }

  $output .= "</div></div>\n";

  return $output;
}

/**
 * Overrrides theme_form_elemenet_label().  Returns HTML for a form element label and required marker.
 *
 * Changes some of the classes and markup to match Twitter Bootstraps classing.
 *
 * Taken from d.o/project/bootstrap
 */
function wise_form_element_label(&$variables) {
  $element = $variables['element'];
  // This is also used in the installer, pre-database setup.
  $t = get_t();

  // If title and required marker are both empty, output no label.
  if ((!isset($element['#title']) || $element['#title'] === '') && empty($element['#required'])) {
    return '';
  }

  // If the element is required, a required marker is appended to the label.
  $required = !empty($element['#required']) ? theme('form_required_marker', array('element' => $element)) : '';

  $title = filter_xss_admin($element['#title']);

  $attributes = array();
  // Style the label as class option to display inline with the element.
  if ($element['#title_display'] == 'after') {
    $attributes['class'][] = 'option';
    $attributes['class'][] = $element['#type'];
  }
  // Show label only to screen readers to avoid disruption in visual flows.
  elseif ($element['#title_display'] == 'invisible') {
    $attributes['class'][] = 'element-invisible';
  }

  if (!empty($element['#id'])) {
    $attributes['for'] = $element['#id'];
  }

  // @Bootstrap: Add Bootstrap control-label class.
  $attributes['class'][] = 'control-label';

  // @Bootstrap: Insert radio and checkboxes inside label elements.
  $output = '';
  if ( isset($variables['#children']) ) {
    $output .= $variables['#children'];
  }

  // @Bootstrap: Append label
  $output .= $t('!title !required', array('!title' => $title, '!required' => $required));

  // The leading whitespace helps visually separate fields from inline labels.
  return ' <label' . drupal_attributes($attributes) . '>' . $output . "</label>\n";
}

/**
 * Overrides theme_button(). Returns HTML for a button form element.
 *
 * Taken from d.o/project/bootstrap
 */
function wise_button($variables) {
  $element = $variables['element'];
  $label = check_plain($element['#value']);
  element_set_attributes($element, array('id', 'name', 'value', 'type'));

  $element['#attributes']['class'][] = 'form-' . $element['#button_type'];
  if (!empty($element['#attributes']['disabled'])) {
    $element['#attributes']['class'][] = 'form-button-disabled';
  }

  // This line break adds inherent margin between multiple buttons
  return '<button' . drupal_attributes($element['#attributes']) . '>'. $label .'</button>' . "\n";
}

/**
 * Overrides theme_item_list().
 *
 * Taken from d.o/project/bootstrap
 */
function wise_item_list($variables) {
  $items = $variables['items'];
  $title = $variables['title'];
  $type = $variables['type'];
  $attributes = $variables['attributes'];
  $output = '';

  // Only output the list container and title, if there are any list items.
  // Check to see whether the block title exists before adding a header.
  // Empty headers are not semantic and present accessibility challenges.
  if (isset($title) && $title !== '') {
    $output .= '<h3>' . $title . '</h3>';
  }

  if (!empty($items)) {
    $output .= "<$type" . drupal_attributes($attributes) . '>';
    $num_items = count($items);
    foreach ($items as $i => $item) {
      $attributes = array();
      $children = array();
      $data = '';
      if (is_array($item)) {
        foreach ($item as $key => $value) {
          if ($key == 'data') {
            $data = $value;
          }
          elseif ($key == 'children') {
            $children = $value;
          }
          else {
            $attributes[$key] = $value;
          }
        }
      }
      else {
        $data = $item;
      }
      if (count($children) > 0) {
        // Render nested list.
        $data .= theme_item_list(array('items' => $children, 'title' => NULL, 'type' => $type, 'attributes' => $attributes));
      }
      if ($i == 0) {
        $attributes['class'][] = 'first';
      }
      if ($i == $num_items - 1) {
        $attributes['class'][] = 'last';
      }
      $output .= '<li' . drupal_attributes($attributes) . '>' . $data . "</li>\n";
    }
    $output .= "</$type>";
  }

  return $output;
}

/**
 * Override theme_filter_tips().
 * Hide the filter tips information.
 */
function wise_filter_tips($vars) {
  return '';
}

/**
 * Override theme_filter_tips_more_info().
 * Hide the filter tips more info link.
 */
function wise_filter_tips_more_info($vars) {
  return '';
}

/**
 * Overrides theme_tablesort_indicator().
 */
function wise_tablesort_indicator($variables) {
  if ($variables['style'] == 'asc') {
    return '<i class="icon-caret-down sort-asc"></i>';
  }
  else {
    return '<i class="icon-caret-up sort-desc"></i>';
  }
}

/**
 * Implements hook_preprocess_views_view().
 */
function wise_preprocess_views_view(&$vars) {
  $view = $vars['view'];

  if ($view->name == 'service_list' && $view->current_display == 'page' && !empty($view->exposed_input)) {
    $vars['attachment_before'] = FALSE;
  }
}

/**
 * Implements hook_preprocess_service_links_node_format().
 */
function wise_preprocess_service_links_node_format(&$vars) {

  foreach ($vars['links'] as $service => $link) {
    $vars['links'][$service]['title'] = t('Share on !service', array('!service' => $link['title']));

    if (in_array($service, array('service-links-facebook', 'service-links-twitter'))) {
      switch ($service) {
        case 'service-links-facebook':
          if ($vars['view_mode'] == 'full') {
            $icon_class = 'icon-facebook';
          }
          else {
            $icon_class = 'icon-facebook-sign';
          }
          break;
        case 'service-links-twitter':
          $icon_class = 'icon-twitter';
          break;
      }
      $vars['links'][$service]['title'] = '<i class="' . $icon_class . '" aria-hidden="true"></i><span class="label">' . $vars['links'][$service]['title'] . '</span>';
      $vars['links'][$service]['html'] = TRUE;
    }
  }
}

/**
 * Override theme_service_links_node_format().
 */
function wise_service_links_node_format($variables) {
  $links = $variables['links'];
  $label = $variables['label'];
  $view_mode = $variables['view_mode'];

  if ($view_mode == 'rss') {
    $result = array();
    foreach($links as $l) {
      $result[] = l($l['title'], $l['href'], $l);
    }

    return '<div class="service-links service-links-' . $view_mode . '">' . implode(' ', $result) . '</div>';
  }

  if (isset($label) && !empty($label)) {
    return '<div class="service-links service-links-' . $view_mode . '"><div class="service-label">'. t('@label', array('@label' => $label)) .' </div>'. theme('links', array('links' => $links)) .'</div>';
  }
  else {
    return '<div class="service-links service-links-' . $view_mode . '">'. theme('links', array('links' => $links)) .'</div>';
  }
}

/**
 * Overrides theme_recaptcha_custom_widget().
 */
function wise_recaptcha_custom_widget() {
  $recaptcha_only_if_incorrect_sol = t('Incorrect please try again');
  $recaptcha_only_if_image_enter = t('Type the text:');
  $recaptcha_only_if_audio_enter = t('Enter the words you hear:');
  $recaptcha_get_another_captcha = t('Get another CAPTCHA');
  $recaptcha_only_if_image = t('Get an audio CAPTCHA');
  $recaptcha_only_if_audio = t('Get an image CAPTCHA');
  $help = t('Help');
  return <<<EOT
    <div class="control-group">
      <div id="recaptcha_image"></div>
    </div>
    <div class="recaptcha_only_if_incorrect_sol alert alert-error" style="color:red">$recaptcha_only_if_incorrect_sol</div>
    <div class="control-group">
      <label for="recaptcha_response_field" class="recaptcha_only_if_image">$recaptcha_only_if_image_enter</label>
      <label for="recaptcha_response_field" class="recaptcha_only_if_audio">$recaptcha_only_if_audio_enter</label>
      <input type="text" id="recaptcha_response_field" name="recaptcha_response_field" />
      <div class="recaptcha_get_another_captcha">
        <a href="javascript:Recaptcha.reload()"><i class="icon-repeat"></i><span class="element-invisible">$recaptcha_get_another_captcha</span></a>
      </div>
      <div class="recaptcha_only_if_image">
        <a href="javascript:Recaptcha.switch_type('audio')"><i class="icon-volume-up"></i><span class="element-invisible">$recaptcha_only_if_image</span></a>
      </div>
      <div class="recaptcha_only_if_audio">
        <a href="javascript:Recaptcha.switch_type('image')"><i class="icon-picture"></i><span class="element-invisible">$recaptcha_only_if_audio</span></a>
      </div>
      <div class="recaptcha_help">
        <a href="javascript:Recaptcha.showhelp()"><i class="icon-question-sign"></i><span class="element-invisible">$help</span></a>
      </div>
    </div>
EOT;
}

/**
 * Theme function for a CAPTCHA element.
 *
 * Render it in a fieldset if a description of the CAPTCHA
 * is available. Render it as is otherwise.
 */
function wise_captcha($variables) {
  $element = $variables['element'];

  // Check if we just have hidden inputs, b/c if so, only output the inputs themselves and nothing else.
  $all_hidden = TRUE;
  foreach (element_children($element) as $key) {
    if (!(isset($element[$key]['#type']) && $element[$key]['#type'] == 'hidden')) {
      $all_hidden = FALSE;
      break;
    }
  }
  if ($all_hidden) {
    return drupal_render_children($element);
  }
  else {
    if (!empty($element['#description']) && isset($element['captcha_widgets'])) {
      return '<div class="captcha"><h3>' . t('Prove you\'re not a robot') . '</h3>' . drupal_render_children($element) . '<p class="help-block">' . $element['#description'] . '</p></div>';
    }
    else {
      return '<div class="captcha"><h3>' . t('Prove you\'re not a robot') . '</h3>' . drupal_render_children($element) . '</div>';
    }
  }
}