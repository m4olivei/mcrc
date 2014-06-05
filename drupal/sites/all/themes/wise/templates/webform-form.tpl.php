<?php
/**
 * @file
 * Customize the display of a complete webform.
 *
 * This file may be renamed "webform-form--[nid].tpl.php" to target a specific
 * webform on your site. Or you can leave it "webform-form.tpl.php" to affect
 * all webforms on your site.
 * 
 * You can also add your own custom template suggestions to the theme_hook_suggestions
 * array as you wish, which would use templates such as "webform-form--mycustompath.tpl.php"
 *  
 * Available variables:
 * - $form: The complete form array.
 * - $nid: The node ID of the Webform.
 *
 * The $form array contains two main pieces:
 * - $form['submitted']: The main content of the user-created form.
 * - $form['details']: Internal information stored by Webform.
 */

// Group up the components
$components = element_children($form['submitted']);
$group = array();
?>
<?php foreach ($components as $name): ?>
  <?php
    // Single column types
    if (isset($form['submitted'][$name]['#type']) && in_array($form['submitted'][$name]['#type'], array('textarea', 'date', 'radios', 'fieldset', 'markup'))) {

      if (!empty($group)) {
        ?>
          <div class="row-fluid">
            <div class="span6">
              <?php print render($form['submitted'][$group[0]]); ?>
            </div>
          </div>
        <?php
        $group = array();
      }
      ?>
        <div class="row-fluid">
          <div class="span12">
            <?php print render($form['submitted'][$name]); ?>
          </div>
        </div>
      <?php
    }
    // Two column type fields
    else {

      if (count($group) < 2) {
        $group[] = $name;
      }

      if (count($group) == 2) {
        ?>
          <div class="row-fluid">
            <?php foreach ($group as $col): ?>
              <div class="span6">
                <?php print render($form['submitted'][$col]); ?>
              </div>
            <?php endforeach; ?>
          </div>
        <?php
        $group = array();
      }
    }
  ?>
<?php endforeach; ?>

<?php

  // Always print out the entire $form. This renders the remaining pieces of the
  // form that haven't yet been rendered above.
  print drupal_render_children($form);
