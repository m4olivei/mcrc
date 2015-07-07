<?php
/**
 * Useful shell aliases:
 */
$options['shell-aliases']['pull-live'] = '!drush sql-sync @mcrc.live @mcrc.dev --create-db --no-cache --structure-tables-key=common --sanitize --sanitize-email=user+%uid@localhost -y';
$options['shell-aliases']['pull-live-files'] = '!drush rsync -v @mcrc.live:%files @mcrc.dev:%files';