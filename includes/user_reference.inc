<?php

/**
 * @file
 * Implements dialog functionality for the user_reference module.
 */

/**
 * Implements hook_references_dialog_widgets().
 */
function user_reference_references_dialog_widgets() {
  return array(
    'user_reference_autocomplete' => array(
      'element_type' => 'textfield',
      'entity_type' => 'user',
      'format' => '$label [uid: $entity_id]',
      'operations' => array(
        'search' => array(
          'function' => 'user_reference_dialog_search_link',
          'title' => t('Search Dialog'),
        ),
        'edit' => array(
          'function' => 'user_reference_dialog_edit_link',
          'title' => t('Edit dialog'),
        ),
        'add' => array(
          'function' => 'user_reference_dialog_add_link',
          'title' => t('Add dialog'),
        ),
      ),
    ),
  );
}

function user_reference_dialog_search_link($element, $widget_settings, $field, $instance) {
  $search_link = array(
    array(
    'title' => t('Search'),
    'href' => 'references-dialog/search/' . $instance['entity_type'] . '/' .
       $instance['field_name'] . '/' .
       $instance['bundle'],
    ),
  );
  return $search_link;
}

function user_reference_dialog_edit_link($element, $widget_settings, $field, $instance) {
  return array(
    array(
      'title' => t('Edit'),
      'href' => 'user/' . $element['#default_value'] . '/edit'
    ),
  );
}

function user_reference_dialog_add_link($element, $widget_settings, $field, $instance) {
  return array(
    array(
      'title' => t('Create user'),
      'href' => 'admin/people/create'
    ),
  );
}
