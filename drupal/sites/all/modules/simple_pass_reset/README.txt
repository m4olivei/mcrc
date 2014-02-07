Simple Password Reset is a module for Drupal 7.x which changes the user experience when resetting their password.  Also setting the password the first time.

Without this module, Drupal emails the user a link to a "one-time login" page.  On that page, they click "Log in" and on the next page they may edit their password.

With this module, Drupal emails a link and on that page the user may edit his/her password.  That is, the "one-time login" page is skipped entirely.

This is useful because it streamlines the process.  Also, many users find the one-time login page confusing and unexpected.  So not needing that is a good thing.

The idea for this module comes from Dave Cohen, and is described in detail in his blog at http://www.dave-cohen.com/node/1000030.

* Installation

Enable the module as you would any other Drupal 7.x module.

Recommended: change the weight of this module to be higher than system.module.  This is so our form_alter hooks act last.  Usually setting the weight to 1 is sufficient.  The SQL command to accomplish this is:

  update system set weight=1 where name='simple_pass_reset';

Recommended: Under Administration >> Configuration >> People >> Settings >> Password recovery, change the link emailed to the user to the following:

  [user:one-time-login-url]/brief

By appending "/brief" the user is shown a minimal form to change the password, instead of the default profile edit form.


* Issue Queue

Please report problems, suggest improvements, etc on the project issue queue: https://drupal.org/project/issues/simple_pass_reset

When submitting issues, a proper issue begins with the sentence "I read the README.txt."
