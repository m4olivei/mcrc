; ----------------
; Generated makefile from http://drushmake.me
; Permanent URL: http://drushmake.me/file.php?token=5ed0c3f04d3c
; ----------------
;
; This is a working makefile - try it! Any line starting with a `;` is a comment.
;
; NOTE: When you make changes to wise_ip.tar.gz or wise.tar.gz update the version number in the query strings
; below to avoid caching drush's.  Also, make sure to upload a copy of the archives to peapoddev server at
; /var/www/html/

; Core version
; ------------
; Each makefile should begin by declaring the core version of Drupal that all
; projects should be compatible with.

core = 7.x

; API version
; ------------
; Every makefile needs to declare its Drush Make API version. This version of
; drush make uses API version `2`.

api = 2

; Core project
; ------------
; In order for your makefile to generate a full Drupal site, you must include
; a core project. This is usually Drupal core, but you can also specify
; alternative core projects like Pressflow. Note that makefiles included with
; install profiles *should not* include a core project.

; Drupal 7.x. Requires the `core` property to be set to 7.x.
projects[drupal][version] = 7.24



; Modules
; --------
projects[ctools][version] = 1.3
projects[ctools][type] = "module"
projects[date][version] = 2.6
projects[date][type] = "module"
projects[devel][version] = 1.3
projects[devel][type] = "module"
projects[diff][version] = 3.2
projects[diff][type] = "module"
projects[entity][version] = 1.2
projects[entity][type] = "module"
projects[features][version] = 2.0
projects[features][type] = "module"
projects[imce][version] = 1.7
projects[imce][type] = "module"
projects[link][version] = 1.2
projects[link][type] = "module"
projects[filefield_sources][version] = 1.9
projects[filefield_sources][type] = "module"
projects[globalredirect][version] = 1.5
projects[globalredirect][type] = "module"
projects[google_analytics][version] = 1.4
projects[google_analytics][type] = "module"
projects[logintoboggan][version] = 1.3
projects[logintoboggan][type] = "module"
projects[menu_block][version] = 2.3
projects[menu_block][type] = "module"
projects[menu_breadcrumb][version] = 1.5
projects[menu_breadcrumb][type] = "module"
projects[pathauto][version] = 1.2
projects[pathauto][type] = "module"
projects[oauth][version] = 3.1
projects[oauth][type] = "module"
projects[oembed][version] = 1.0-rc2
projects[oembed][type] = "module"
projects[redirect][version] = 1.0-rc1
projects[redirect][type] = "module"
projects[smart_trim][version] = 1.4
projects[smart_trim][type] = "module"
projects[strongarm][version] = 2.0
projects[strongarm][type] = "module"
projects[token][version] = 1.5
projects[token][type] = "module"
projects[transliteration][version] = 3.1
projects[transliteration][type] = "module"
projects[twitter][version] = 5.8
projects[twitter][type] = "module"
projects[imce_wysiwyg][version] = 1.0
projects[imce_wysiwyg][type] = "module"
projects[imce_mkdir][version] = 1.0
projects[imce_mkdir][type] = "module"
projects[wysiwyg][version] = 2.2
projects[wysiwyg][type] = "module"
projects[views][version] = 3.7
projects[views][type] = "module"
projects[webform][version] = 3.19
projects[webform][type] = "module"
projects[xmlsitemap][version] = 2.0-rc2
projects[xmlsitemap][type] = "module"


; Wise & Hammer Modules
projects[wise_slider][type] = "module"
projects[wise_slider][subdir] = "_custom"
projects[wise_slider][download][type] = "file"
projects[wise_slider][download][url] = "http://peapoddev.com/wise_slider.tar.gz"

projects[wise_tweaks][type] = "module"
projects[wise_tweaks][subdir] = "_custom"
projects[wise_tweaks][download][type] = "file"
projects[wise_tweaks][download][url] = "http://peapoddev.com/wise_tweaks.tar.gz"

projects[wise_theme][type] = "module"
projects[wise_theme][subdir] = "_custom"
projects[wise_theme][download][type] = "file"
projects[wise_theme][download][url] = "http://peapoddev.com/wise_theme.tar.gz"

projects[wise_og][type] = "module"
projects[wise_og][subdir] = "_custom"
projects[wise_og][download][type] = "file"
projects[wise_og][download][url] = "http://peapoddev.com/wise_og.tar.gz"

; Themes
; --------
projects[] = zen


; Wise & Hammer Themes
projects[wise][type] = "theme"
projects[wise][download][type] = "file"
projects[wise][download][url] = "http://peapoddev.com/wise.tar.gz"


; Libraries
; ---------
libraries[tinymce][type] = "libraries"
libraries[tinymce][download][type] = "file"
libraries[tinymce][download][url] = "http://download.moxiecode.com/tinymce/tinymce_3.5.9_jquery.zip"


; Wise & Hammer Installation Profiles
; ---------
projects[wise_ip][type] = "profile"
projects[wise_ip][download][type] = "file"
projects[wise_ip][download][url] = "http://peapoddev.com/wise_ip.tar.gz"
