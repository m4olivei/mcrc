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
$num_cols = isset($view->style_options['columns']) ? $view->style_options['columns'] : 4;

// Take the first row and lay it out in half the number of columns as configured.
$featured_rows = array_shift($rows);
$featured_rows = array_chunk($featured_rows, floor($num_cols / 2));
$first = TRUE;
$count = 0;
?>
<?php if (!empty($title)) : ?>
  <h3><?php print $title; ?></h3>
<?php endif; ?>
<div class="row-set row-set-featured">
  <?php foreach ($featured_rows as $columns): ?>
    <?php $count++; ?>
    <div class="row-fluid<?php print $first ? ' row-first' : ''; ?><?php print $count == count($featured_rows) ? ' row-last' : ''; ?>">
      <?php foreach ($columns as $column_number => $item): ?>
        <div class="cell span<?php echo floor(12 / ($num_cols / 2)); ?>">
          <?php print $item; ?>
        </div>
      <?php endforeach; ?>
    </div>
    <?php $first = FALSE; ?>
  <?php endforeach; ?>
</div>

<div class="row-set row-set-other">
  <?php foreach ($rows as $row_number => $columns): ?>
    <div class="row-fluid <?php print $row_classes[$row_number]; ?>">
      <?php foreach ($columns as $column_number => $item): ?>
        <div class="cell span<?php echo floor(12 / $num_cols); ?>">
          <?php print $item; ?>
        </div>
      <?php endforeach; ?>
    </div>
  <?php endforeach; ?>
</div>