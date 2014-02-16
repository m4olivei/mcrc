<?php
/**
 * @file
 * mcrc_services.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function mcrc_services_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'service_list';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Service list';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Listen to the Message';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['link_display'] = 'page';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '25';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['pager']['options']['tags']['first'] = '< First';
  $handler->display->display_options['pager']['options']['tags']['previous'] = '< Previous';
  $handler->display->display_options['pager']['options']['tags']['next'] = 'Next >';
  $handler->display->display_options['pager']['options']['tags']['last'] = 'Last >';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['default_row_class'] = FALSE;
  $handler->display->display_options['style_options']['row_class_special'] = FALSE;
  $handler->display->display_options['style_options']['columns'] = array(
    'field_service_audio' => 'field_service_audio',
    'title' => 'title',
    'field_service_pastor' => 'field_service_pastor',
    'field_service_date' => 'field_service_date',
    'field_service_date_1' => 'field_service_date_1',
  );
  $handler->display->display_options['style_options']['default'] = 'field_service_date';
  $handler->display->display_options['style_options']['info'] = array(
    'field_service_audio' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'title' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_service_pastor' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_service_date' => array(
      'sortable' => 1,
      'default_sort_order' => 'desc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_service_date_1' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Field: Content: Audio */
  $handler->display->display_options['fields']['field_service_audio']['id'] = 'field_service_audio';
  $handler->display->display_options['fields']['field_service_audio']['table'] = 'field_data_field_service_audio';
  $handler->display->display_options['fields']['field_service_audio']['field'] = 'field_service_audio';
  $handler->display->display_options['fields']['field_service_audio']['label'] = '';
  $handler->display->display_options['fields']['field_service_audio']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_service_audio']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_service_audio']['type'] = 'soundmanager2_inline_player';
  $handler->display->display_options['fields']['field_service_audio']['settings'] = array(
    'pause' => 'pause',
    'text' => 'title',
  );
  /* Field: Content: Audio */
  $handler->display->display_options['fields']['field_service_audio_1']['id'] = 'field_service_audio_1';
  $handler->display->display_options['fields']['field_service_audio_1']['table'] = 'field_data_field_service_audio';
  $handler->display->display_options['fields']['field_service_audio_1']['field'] = 'field_service_audio';
  $handler->display->display_options['fields']['field_service_audio_1']['label'] = '';
  $handler->display->display_options['fields']['field_service_audio_1']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_service_audio_1']['alter']['text'] = '<a href="[field_service_audio_1]" title="Download MP3" class="inline-exclude"><i class="icon-cloud-download"></i></a>';
  $handler->display->display_options['fields']['field_service_audio_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_service_audio_1']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_service_audio_1']['type'] = 'file_url_plain';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Pastor */
  $handler->display->display_options['fields']['field_service_pastor']['id'] = 'field_service_pastor';
  $handler->display->display_options['fields']['field_service_pastor']['table'] = 'field_data_field_service_pastor';
  $handler->display->display_options['fields']['field_service_pastor']['field'] = 'field_service_pastor';
  $handler->display->display_options['fields']['field_service_pastor']['delta_offset'] = '0';
  /* Field: Content: Date */
  $handler->display->display_options['fields']['field_service_date']['id'] = 'field_service_date';
  $handler->display->display_options['fields']['field_service_date']['table'] = 'field_data_field_service_date';
  $handler->display->display_options['fields']['field_service_date']['field'] = 'field_service_date';
  $handler->display->display_options['fields']['field_service_date']['settings'] = array(
    'format_type' => 'short',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Content: Date */
  $handler->display->display_options['fields']['field_service_date_1']['id'] = 'field_service_date_1';
  $handler->display->display_options['fields']['field_service_date_1']['table'] = 'field_data_field_service_date';
  $handler->display->display_options['fields']['field_service_date_1']['field'] = 'field_service_date';
  $handler->display->display_options['fields']['field_service_date_1']['label'] = 'AM/PM';
  $handler->display->display_options['fields']['field_service_date_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_service_date_1']['settings'] = array(
    'format_type' => 'am_pm',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Sort criterion: By service date */
  $handler->display->display_options['sorts']['field_service_date_value']['id'] = 'field_service_date_value';
  $handler->display->display_options['sorts']['field_service_date_value']['table'] = 'field_data_field_service_date';
  $handler->display->display_options['sorts']['field_service_date_value']['field'] = 'field_service_date_value';
  $handler->display->display_options['sorts']['field_service_date_value']['ui_name'] = 'By service date';
  $handler->display->display_options['sorts']['field_service_date_value']['order'] = 'DESC';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'service' => 'service',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Search: Search Terms */
  $handler->display->display_options['filters']['keys']['id'] = 'keys';
  $handler->display->display_options['filters']['keys']['table'] = 'search_index';
  $handler->display->display_options['filters']['keys']['field'] = 'keys';
  $handler->display->display_options['filters']['keys']['exposed'] = TRUE;
  $handler->display->display_options['filters']['keys']['expose']['operator_id'] = 'keys_op';
  $handler->display->display_options['filters']['keys']['expose']['label'] = 'By Keyword ...';
  $handler->display->display_options['filters']['keys']['expose']['operator'] = 'keys_op';
  $handler->display->display_options['filters']['keys']['expose']['identifier'] = 'keys';
  $handler->display->display_options['filters']['keys']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
    7 => 0,
    8 => 0,
    9 => 0,
    10 => 0,
    11 => 0,
    12 => 0,
  );
  /* Filter criterion: Content: Pastor (field_service_pastor) */
  $handler->display->display_options['filters']['field_service_pastor_tid']['id'] = 'field_service_pastor_tid';
  $handler->display->display_options['filters']['field_service_pastor_tid']['table'] = 'field_data_field_service_pastor';
  $handler->display->display_options['filters']['field_service_pastor_tid']['field'] = 'field_service_pastor_tid';
  $handler->display->display_options['filters']['field_service_pastor_tid']['value'] = '';
  $handler->display->display_options['filters']['field_service_pastor_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_service_pastor_tid']['expose']['operator_id'] = 'field_service_pastor_tid_op';
  $handler->display->display_options['filters']['field_service_pastor_tid']['expose']['label'] = 'By Pastor ...';
  $handler->display->display_options['filters']['field_service_pastor_tid']['expose']['operator'] = 'field_service_pastor_tid_op';
  $handler->display->display_options['filters']['field_service_pastor_tid']['expose']['identifier'] = 'pastor';
  $handler->display->display_options['filters']['field_service_pastor_tid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
    7 => 0,
    8 => 0,
    9 => 0,
    10 => 0,
    11 => 0,
    12 => 0,
  );
  $handler->display->display_options['filters']['field_service_pastor_tid']['vocabulary'] = 'pastors';
  /* Filter criterion: Date: Date (node) */
  $handler->display->display_options['filters']['date_filter']['id'] = 'date_filter';
  $handler->display->display_options['filters']['date_filter']['table'] = 'node';
  $handler->display->display_options['filters']['date_filter']['field'] = 'date_filter';
  $handler->display->display_options['filters']['date_filter']['exposed'] = TRUE;
  $handler->display->display_options['filters']['date_filter']['expose']['operator_id'] = 'date_filter_op';
  $handler->display->display_options['filters']['date_filter']['expose']['label'] = 'By Date ...';
  $handler->display->display_options['filters']['date_filter']['expose']['operator'] = 'date_filter_op';
  $handler->display->display_options['filters']['date_filter']['expose']['identifier'] = 'date';
  $handler->display->display_options['filters']['date_filter']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
    7 => 0,
    8 => 0,
    9 => 0,
    10 => 0,
    11 => 0,
    12 => 0,
  );
  $handler->display->display_options['filters']['date_filter']['form_type'] = 'date_popup';
  $handler->display->display_options['filters']['date_filter']['year_range'] = '-5:+0';
  $handler->display->display_options['filters']['date_filter']['date_fields'] = array(
    'field_data_field_service_date.field_service_date_value' => 'field_data_field_service_date.field_service_date_value',
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['header'] = FALSE;
  /* Header: Global: Unfiltered text */
  $handler->display->display_options['header']['area_text_custom']['id'] = 'area_text_custom';
  $handler->display->display_options['header']['area_text_custom']['table'] = 'views';
  $handler->display->display_options['header']['area_text_custom']['field'] = 'area_text_custom';
  $handler->display->display_options['header']['area_text_custom']['label'] = 'RSS Link';
  $handler->display->display_options['header']['area_text_custom']['empty'] = TRUE;
  $handler->display->display_options['header']['area_text_custom']['content'] = '<a href="/resources/listen-to-the-message/rss.xml" class="rss rss-messages" target="_blank"><i class="icon-rss"></i></a>';
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['content'] = 'Listen to Sunday’s messages! Directly below you\'ll see our most recent message. Below the most recent message is a listing of previous messages. May you be blessed by browsing through more than 4 years of recorded messages at Mountainview CRC!';
  $handler->display->display_options['header']['area']['format'] = 'full_html';
  $handler->display->display_options['defaults']['empty'] = FALSE;
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = 'There are no results for the given search criteria.';
  $handler->display->display_options['empty']['area']['format'] = 'wysiwyg';
  $handler->display->display_options['path'] = 'resources/listen-to-the-message';

  /* Display: Attachment */
  $handler = $view->new_display('attachment', 'Attachment', 'attachment_1');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '1';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'node';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'service' => 'service',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'default' => 0,
  );
  $handler->display->display_options['inherit_arguments'] = FALSE;

  /* Display: Feed */
  $handler = $view->new_display('feed', 'Feed', 'feed_1');
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'rss';
  $handler->display->display_options['row_plugin'] = 'node_rss';
  $handler->display->display_options['path'] = 'resources/listen-to-the-message/rss.xml';
  $export['service_list'] = $view;

  return $export;
}
