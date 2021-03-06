<?php
/**
 * @file
 * wise_slider.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function wise_slider_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'wise_slider';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Slider';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['css_class'] = 'container';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '5';
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['style_options']['default_row_class'] = FALSE;
  $handler->display->display_options['style_options']['row_class_special'] = FALSE;
  $handler->display->display_options['style_options']['class'] = 'slides';
  $handler->display->display_options['style_options']['wrapper_class'] = 'flexslider';
  $handler->display->display_options['row_plugin'] = 'node';
  $handler->display->display_options['row_options']['links'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Sort criterion: Content: Sticky */
  $handler->display->display_options['sorts']['sticky']['id'] = 'sticky';
  $handler->display->display_options['sorts']['sticky']['table'] = 'node';
  $handler->display->display_options['sorts']['sticky']['field'] = 'sticky';
  $handler->display->display_options['sorts']['sticky']['order'] = 'DESC';
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Slider (field_slider) */
  $handler->display->display_options['filters']['field_slider_tid']['id'] = 'field_slider_tid';
  $handler->display->display_options['filters']['field_slider_tid']['table'] = 'field_data_field_slider';
  $handler->display->display_options['filters']['field_slider_tid']['field'] = 'field_slider_tid';
  $handler->display->display_options['filters']['field_slider_tid']['value'] = array(
    0 => '1',
  );
  $handler->display->display_options['filters']['field_slider_tid']['vocabulary'] = 'slider';

  /* Display: Homepage */
  $handler = $view->new_display('block', 'Homepage', 'block');
  $handler->display->display_options['block_description'] = 'Homepage Slider';

  /* Display: Facilities */
  $handler = $view->new_display('block', 'Facilities', 'block_1');
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Slider (field_slider) */
  $handler->display->display_options['filters']['field_slider_tid']['id'] = 'field_slider_tid';
  $handler->display->display_options['filters']['field_slider_tid']['table'] = 'field_data_field_slider';
  $handler->display->display_options['filters']['field_slider_tid']['field'] = 'field_slider_tid';
  $handler->display->display_options['filters']['field_slider_tid']['value'] = array(
    0 => '308',
  );
  $handler->display->display_options['filters']['field_slider_tid']['vocabulary'] = 'slider';
  $handler->display->display_options['block_description'] = 'Facilities';
  $export['wise_slider'] = $view;

  return $export;
}
