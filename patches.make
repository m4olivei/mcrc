; Patch Drupal core to allow FAPI select, radios, and checkboxes to specify some options as disabled
; @see https://www.drupal.org/node/284917#comment-10091946
projects[drupal][patch][] = "https://www.drupal.org/files/issues/form-disabled-options-284917-65.patch"

; Patch views module to fix a PHP notice
; @see https://www.drupal.org/node/2481401#comment-10752682
projects[views][patch][] = "https://www.drupal.org/files/issues/check_if_exposed_input_exists-2481401-14_0.patch"

; Patch date module to fix a PHP notice
; @see https://www.drupal.org/node/2469189#comment-9811289
projects[date][patch][] = "https://www.drupal.org/files/issues/date-show_remaining_days_notice-2469189-1.patch"

; Patch notify tag to add tag a query to se can alter it.
projects[notify][patch][] = "patches/notify-query_tag.patch
