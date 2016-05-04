# Installation

Please follow documentation for composer manager in order to install this module:
- [General](https://www.drupal.org/node/2405789)
- [Installation with Drush](https://www.drupal.org/node/2405805)

## TL;DR

`drush en sparkpost -y`

## Troubleshooting

If composer plugin for drush haven't been installed yet you may experience
errors during instalation. In order to fix it go above drupal scope (i.e. one
level up from drupal root) and clear drush cache:

 `drush cc drush`

Then go back to your site folder and try to install composer dependencies
once again:

 `drush composer-manager install`

# Configuration

In order to use Sparkpost module you must:

- create account on sparkpost.com,
- verify domain you want use to send messages
- create API key
- grant permission for API key to read and write transmissions
 ("Transmissions: Read/Write")

Now go to drupal site and connect it with your Sparkpost account:

- go to `/admin/config/services/sparkpost` and add Sparkpost API key
- go to `/admin/config/services/sparkpost/test` and test if you are able to
 send messages
- go to `/admin/config/system/mailsystem` and choose `SparkpostMailSystem` as
 Site-wide default MailSystemInterface class

# It doesn't work for me!

If you have any troubles with Sparkpost, please [report it on drupal.org](https://www.drupal.org/project/issues/sparkpost)

# Help

If you think this file could be improved, please go to 
[this issue](https://www.drupal.org/node/2711659) and complain ;)
