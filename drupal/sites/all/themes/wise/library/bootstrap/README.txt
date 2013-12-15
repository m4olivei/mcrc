Twitter Bootstrap "Library"
========================================================================

The contents of the bootstrap directory consist of a SASS port of the Twitter Bootstrap project.  The SASS
project is called bootstrap-sass and is hosted on github here:

https://github.com/thomas-mcdonald/bootstrap-sass

The github project consists of some Ruby stuff that we aren't interested in.  The files taken from the
bootstrap-sass project and their location in this theme are as follows:

vendor/assets/javascripts ---> library/bootstrap/js
vendor/assets/stylesheets ---> library/bootstrap/sass
vendor/assets/images ---> library/bootstrap/images

The twitter bootstrap SASS is brought in using a copy of library/bootstrap/sass/bootstrap/bootstrap.scss at
sass/_bootstrap.scss and a copy of library/bootstrap/sass/bootstrap/responsive.scss, which are included in
sass/style.scss.  That way, we can update the library files without affecting what parts of Twitter Bootstrap is
used in the theme.

The Javascript should be included using Drupal's facilities as needed.