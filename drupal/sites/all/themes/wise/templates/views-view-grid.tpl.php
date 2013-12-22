<?php

/**
 * @file
 * Default simple view template to display a rows in a grid.
 *
 * - $rows contains a nested array of rows. Each row contains an array of
 *   columns.
 *
 * @ingroup views_templates
 */
$num_cols = isset($view->style_options['columns']) ? $view->style_options['columns'] : 3;
?>
<?php if (!empty($title)) : ?>
  <h3><?php print $title; ?></h3>
<?php endif; ?>
<?php foreach ($rows as $row_number => $columns): ?>
  <div class="row-fluid <?php print $row_classes[$row_number]; ?>">
    <?php foreach ($columns as $column_number => $item): ?>
      <div class="cell span<?php echo floor(12 / $num_cols); ?>">
        <?php print $item; ?>
      </div>
    <?php endforeach; ?>
  </div>
<?php endforeach; ?>