<?php

/**
 * @file
 * This file contains views hooks.
 */

/**
 * Implementation of hook_views_plugins().
 */
function references_dialog_views_plugins() {
  return array(
    'cache' => array(
      'rules' => array(
        'title' => t('Reference Search'),
        'help' => t(''),
        'handler' => 'references_dialog_plugin_display_reference_search',
        'help topic' => 'reference-dialog',
        'path' => drupal_get_path('module', 'views') . '/views',
      ),
    ),
  );
}