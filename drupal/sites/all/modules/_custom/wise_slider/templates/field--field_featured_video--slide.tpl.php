<?php
/**
 * @file
 * Field template for field_featured_video on the slide node type.  Overriden to get rid of extraneous markup.
 */
?>
<?php foreach ($items as $delta => $item): ?>
  <?php print render($item); ?>
<?php endforeach; ?>
