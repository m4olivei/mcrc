<?php
/**
 * @file
 * Node template for the homepage slides.  Style the same irregardless of view_mode.
 */
hide($content['comments']);
hide($content['links']);
?>
<article class="slide-image node-<?php print $node->nid; ?> <?php print $classes; ?> clearfix"<?php print $attributes; ?>>

  <?php if (isset($content['field_slide_video'])): ?>
    <?php print render($content['field_slide_video']); ?>
  <?php else: ?>
    <div class="slide-image">
      <?php print render($content['field_slide_image']); ?>
      <?php if (isset($node->field_slide_tagline['und'][0]['value'])): ?>
        <div class="slide-text span5">
          <div class="slide-title"><?php print $title; ?></div>
          <div class="slide-tagline"><?php print render($content['field_slide_tagline'][0]); ?></div>
          <?php if (isset($node->field_slide_link['und'][0]['url'])): ?>
            <?php print l($node->field_slide_link['und'][0]['title'], $node->field_slide_link['und'][0]['url'], array('attributes' => array('class' => array('btn btn-primary')))); ?>
          <?php endif; ?>
        </div>
      <?php endif; ?>
    </div>
  <?php endif; ?>

</article>