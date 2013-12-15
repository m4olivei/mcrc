# Wise & Hammer

The Wise & Hammer (wise) theme is a Zen (http://drupal.org/project/zen) child theme that is meant to be used as a starting point for a Drupal 7 theme for a client website.  Zen is used as a base theme for its excellent core template overrides, that introduce HTML5 markup where it makes sense.  Zen also provides some handy theme function overrides in it's template.php which are good to have. The theme also incorporates a SASS port of Bootstrap, overriding core markup to line up with Bootstrap markup and classes.

## Working Files

The intention is that you obtain and use a copy of the wise theme at the start of a client project.  The space in which you will work should consist only of the following set of files/folder within the theme.  Other files/folders should be left alone, or changes ported to the wise repository:

* images  
Place any images for the theme in this folder.
* images-source  
If you have any PSD files that are used to aid the creation of images, place them here.
* js
 * script.js  
   For quick, simple, small JS enhancements
* library  
  If you use any JS/CSS libraries, put the source code here in it's own folder.
* sass  
  Site style.
 * _base.scss
   _base.scss is the place to define any custom SASS variables and mixins.  Things like font stacks, and color pallets should be defined here.  If you're using a particular compass plugin, it should be included here as well.
 * _bootstrap.scss
   This file includes all the Bootstrap SASS.  If you're theme doesn't use some parts, comment those parts out.  This file is a copy of library/bootstrap/sass/bootstrap.css.scss.
 * _custom.scss
   Put any custom SASS mixins here.
 * _custom_bootstrap_mixins.scss
   Bootstrap is highly configurable, define any mixin overrides from Bootstrap here.  See library/bootstrap/sass/bootstrap/_variables.scss for details.
 * _custom_bootstrap_variables.scss
   Bootstrap is highly configurable, define any variable overrides from Bootstrap here.  See library/bootstrap/sass/bootstrap/_mixins.scss for details.
 * _footer.scss
   Footer styles for the site go here.
 * _header.scss
   Header styles for the site go here.
 * _modules.scss
   Any other site styles go into this file.  Note there is nothing that says you can't break out into another file for significantly large parts of style.  Try to style in an OOCSS fasion where, intelligent class names are used generically to maximize reuse.
* templates  
  Put any Drupal template overrides here.  The ones included are from Zen theme.
* favicon.ico  
  Replace with the client's favicon.
* logo.png
  Replace with the client's logo.
* wise.info
  Add/remove regions as per requirements.
* screenshot.png
  Replace with a complete/semi-complete screenshot of the theme.
* template.php
  Put any theme function overrides, preprocess/process functions, or other hooks into Drupal in this file.

## Other files included with Wise & Hammer (Core files)

* css  
  Compiled CSS.  During development, use compass to watch the theme folder, which will automatically compile the SASS as you work.
* sass  
 * _modules_default.scss  
   Default Drupal style overrides all sites will need.
 * print.scss  
   Print styles from Zen theme.
* .gitignore  
  Theme specific git ignore patterns.
* config.rb  
  Compass configuration.
* README.txt  
  This markdown documentation.
* template_default.php  
  Default theme function, process/preprocess functions and other Drupal hooks.  Much of this is implemented to alter the markup Drupal puts out slightly to match Bootstraps expected markup and classes.
* theme-settings.php  
  Inherited from Zen theme, not really important.

## Making Changes to the Wise & Hammer Core Files

The wise theme is tracked in a repository on peapoddev at:

ssh://root@peapoddev.com/var/git/peapod_code/drupal/themes/wise

Any changes to core files should be pushed back into the repository for use on later projects.  When updating the repository, be sure to also upload an export of the theme for use with the Wise & Hammer installation profile.  Execute the following command on a local copy of the Git repository:

```bash
git archive --format=tar master | gzip > wise.tar.gz
```

Then upload wise.tar.gz to /var/www/html:

```bash
scp wise.tar.gz root@peapoddev.com:/var/www/html/
```

## Resources

* [[Zen theme|http://drupal.org/project/zen]]
* [[Twitter Bootstrap|http://twitter.github.com/bootstrap/]]
* [[https://github.com/yabawock/bootstrap-sass-rails]]
* [[FitVids|http://fitvidsjs.com/]]