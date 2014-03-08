<?php
/**
 * @file
 * Returns the HTML for a node.
 *
 * Complete documentation for this file is available online.
 * @see https://drupal.org/node/1728164
 */
?>
<article class="node-<?php print $node->nid; ?> <?php print $classes; ?> clearfix"<?php print $attributes; ?>>

  <header class="clearfix">
    <?php if (!empty($content['field_service_audio'])): ?>
      <div class="audio">
        <?php print render($content['field_service_audio']); ?>
      </div>
    <?php endif; ?>

    <div class="meta">
      <?php if ($display_submitted): ?>
        <p class="submitted">
          <?php print $user_picture; ?>
          <?php print $submitted; ?>
        </p>
      <?php endif; ?>

      <?php print render($content['field_service_date']); ?>

      <?php if ($title_prefix || $title_suffix || $display_submitted || $unpublished || !$page && $title): ?>
        <?php print render($title_prefix); ?>
        <?php if (!$page && $title): ?>
          <h2<?php print $title_attributes; ?>><a href="<?php print $node_url; ?>"><?php print $title; ?></a></h2>
        <?php endif; ?>
        <?php print render($title_suffix); ?>
      <?php endif; ?>

      <?php print render($content['field_service_pastor']); ?>
      <?php if (isset($content['field_service_passage'])): ?>
        <?php print render($content['field_service_passage']); ?>
      <?php endif; ?>

      <?php if ($unpublished): ?>
        <mark class="unpublished"><?php print t('Unpublished'); ?></mark>
      <?php endif; ?>
    </div>
  </header>

  <div class="content">
    <?php
      // We hide the comments and links now so that we can render them later.
      hide($content['comments']);
      hide($content['links']);
      hide($content['service_links']);
      print render($content);
    ?>

    <div class="download-service-links clearfix">
      <?php print l('<i class="icon-cloud-download"></i><span class="element-invisible">' . t('Download MP3') . '</span>', file_create_url($node->field_service_audio[LANGUAGE_NONE][0]['uri']), array('html' => TRUE, 'attributes' => array('class' => array('download-link'), 'title' => t('Download MP3')))); ?>
      <?php print render($content['service_links']); ?>
    </div>

    <?php print render($content['links']); ?>

    <?php print render($content['comments']); ?>
  </div>

</article>
