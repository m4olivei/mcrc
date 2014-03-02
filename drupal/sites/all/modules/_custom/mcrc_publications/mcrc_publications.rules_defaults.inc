<?php
/**
 * @file
 * mcrc_publications.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function mcrc_publications_default_rules_configuration() {
  $items = array();
  $items['mcrc_publications_church_family_notification'] = entity_import('rules_config', '{ "mcrc_publications_church_family_notification" : {
      "LABEL" : "Church family notification",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "MCRC" ],
      "REQUIRES" : [ "rules", "views_bulk_operations" ],
      "ON" : { "node_insert--publication" : { "bundle" : "publication" } },
      "IF" : [
        { "data_is" : { "data" : [ "node:field-publication-type:tid" ], "value" : "292" } }
      ],
      "DO" : [
        { "views_bulk_operations_action_load_list" : {
            "USING" : { "view" : "publication_notification_user_group|default", "args" : "3" },
            "PROVIDE" : { "entity_list" : { "user_list" : "User list" } }
          }
        },
        { "LOOP" : {
            "USING" : { "list" : [ "user-list" ] },
            "ITEM" : { "user_item" : "Current user" },
            "DO" : [
              { "mail" : {
                  "to" : "[user-item:mail]",
                  "subject" : "A new [node:field-publication-type] has been posted",
                  "message" : "Hello [user-item:name],\\r\\n\\r\\nA new [node:field-publication-type] has been posted.  You can download the publication by following the link below:\\r\\n\\r\\n[site:url]system\\/files\\/publications\\/[node:field-publication-file:file:basename]\\r\\n\\r\\nIf you wish to stop receiving these notifications, login to your account and adjust your notification preferences: [site:url]user.\\r\\n\\r\\nThank you,\\r\\nThe Web Ministry Team",
                  "from" : "office@mountainviewcrc.org",
                  "language" : [ "" ]
                }
              }
            ]
          }
        }
      ]
    }
  }');
  $items['mcrc_publications_weekly_bulletin_notification'] = entity_import('rules_config', '{ "mcrc_publications_weekly_bulletin_notification" : {
      "LABEL" : "Weekly bulletin notification",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "MCRC" ],
      "REQUIRES" : [ "rules", "views_bulk_operations" ],
      "ON" : { "node_insert--publication" : { "bundle" : "publication" } },
      "IF" : [
        { "data_is" : { "data" : [ "node:field-publication-type:tid" ], "value" : "290" } }
      ],
      "DO" : [
        { "views_bulk_operations_action_load_list" : {
            "USING" : { "view" : "publication_notification_user_group|default", "args" : "1" },
            "PROVIDE" : { "entity_list" : { "user_list" : "User list" } }
          }
        },
        { "LOOP" : {
            "USING" : { "list" : [ "user-list" ] },
            "ITEM" : { "user_item" : "Current user" },
            "DO" : [
              { "mail" : {
                  "to" : "[user-item:mail]",
                  "subject" : "A new [node:field-publication-type] has been posted",
                  "message" : "Hello [user-item:name],\\r\\n\\r\\nA new [node:field-publication-type] has been posted.  You can download the publication by following the link below:\\r\\n\\r\\n[site:url]system\\/files\\/publications\\/[node:field-publication-file:file:basename]\\r\\n\\r\\nIf you wish to stop receiving these notifications, login to your account and adjust your notification preferences: [site:url]user.\\r\\n\\r\\nThank you,\\r\\nThe Web Ministry Team",
                  "from" : "office@mountainviewcrc.org",
                  "language" : [ "" ]
                }
              }
            ]
          }
        }
      ]
    }
  }');
  $items['rules_weekly_newsletter_notification'] = entity_import('rules_config', '{ "rules_weekly_newsletter_notification" : {
      "LABEL" : "Weekly newsletter notification",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "MCRC" ],
      "REQUIRES" : [ "rules", "views_bulk_operations" ],
      "ON" : { "node_insert--publication" : { "bundle" : "publication" } },
      "IF" : [
        { "data_is" : { "data" : [ "node:field-publication-type:tid" ], "value" : "291" } }
      ],
      "DO" : [
        { "views_bulk_operations_action_load_list" : {
            "USING" : { "view" : "publication_notification_user_group|default", "args" : "2" },
            "PROVIDE" : { "entity_list" : { "user_list" : "User list" } }
          }
        },
        { "LOOP" : {
            "USING" : { "list" : [ "user-list" ] },
            "ITEM" : { "user_item" : "Current user" },
            "DO" : [
              { "mail" : {
                  "to" : "[user-item:mail]",
                  "subject" : "A new [node:field-publication-type] has been posted",
                  "message" : "Hello [user-item:name],\\r\\n\\r\\nA new [node:field-publication-type] has been posted.  You can download the publication by following the link below:\\r\\n\\r\\n[site:url]system\\/files\\/publications\\/[node:field-publication-file:file:basename]\\r\\n\\r\\nIf you wish to stop receiving these notifications, login to your account and adjust your notification preferences: [site:url]user.\\r\\n\\r\\nThank you,\\r\\nThe Web Ministry Team",
                  "from" : "office@mountainviewcrc.org",
                  "language" : [ "" ]
                }
              }
            ]
          }
        }
      ]
    }
  }');
  return $items;
}
