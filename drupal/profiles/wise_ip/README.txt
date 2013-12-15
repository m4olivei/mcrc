Wise & Hammer Install Profile
========================================================================

The Wise & Hammer Install Profile is meant as an aid to ramp up development on a Drupal site.  There is a make
file provided that can be used with drush make, to download all the necessary modules, libraries and indeed
even the Wise & Hammer profile itself, which is hosted at http://peapoddev.com/wise_ip.tar.gz.

Note that anytime you make changes to the Wise & Hammer Install Profile, you should package it up into wise_ip.tar.gz, upload
it to the peapoddev server at /var/www/html/ and update the Make file to increment the version number in order
to avoid Drush caching issues.

The Wise & Hammer Install Profile accomplises the following:

1. Enables core and contrib modules:

See the wise_ip.info file to see which modules from core and contrib are enabled by the install profile.

2. Installs the following text formats:

Filtered HTML
Full HTML
Limited WYSIWYG
WYSIWYG

3. Blocks enabled and placed appropriately:

System help
Main page content
Navigation
Switch User (Dashboard)
Search (Dashboard)

4. Content types and fields

Basic Page w/ Image field

5. Account settings

Enable user pictures and sensible defaults
Set registration to admin only

6. Roles and permissions

Create a new Content Administrator role
Create a Site Administrator role, set to have all permissions
Create a content_admin user in the Content Administrator role

7. Save a link to the homepage in the Main Menu

8. Set some sensible defaults for theme settings

9. Set the system email to dev@wiseandhammer.com

10. Setup default settings for a number of contrib modules

Set page and default node path pattern for pathauto
Setup WYSIWYG profiles
Setup IMCE profiles
Set logintoboggan to show user login form on access denied
Configure XMLSiteMap to index the main menu

Notes
========================================================================

The code for the Wise & Hammer Install Profile is maintained in a git repo.  To make changes, clone the repo:

git clone ssh://root@peapoddev.com/var/git/wise_d7_ip wise_ip

The file d7.make.inc is a Drush Make file that can be used to download all the necessary source code for the
install profile and its dependancies.