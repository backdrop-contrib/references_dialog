<?php

/**
 * @file
 * Implements dialog functionality for the node_reference module.
 */

/**
 * Implements hook_references_dialog_widgets().
 */
function node_reference_references_dialog_widgets() {
  return array(
    'node_reference_autocomplete' => array(
      'element_type' => 'textfield',
      'dialog_form' => 'node_reference_dialog_form',
      'entity_type' => 'node',
      'format' => '$label [nid: $entity_id]',
      'views_query' => 'node_reference_dialog_views_query',
      'operations' => array(
        'search' => array(
          'function' => 'node_reference_dialog_search_link',
          'title' => t('Search Dialog'),
        ),
        'edit' => array(
          'function' => 'node_reference_dialog_edit_link',
          'title' => t('Edit dialog'),
        ),
        'add' => array(
          'function' => 'node_reference_dialog_add_link',
          'title' => t('Add dialog'),
        ),
      ),
    ),
  );
}

function node_reference_dialog_search_link($element, $widget_settings, $field, $instance) {
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

function node_reference_dialog_edit_link($element, $widget_settings, $field, $instance) {
  if (isset($element['#default_value'])) {
    $node = node_load($element['#default_value']);
    if (node_access('update', $node)) {
      return array(
        array(
          'title' => t('Edit'),
          'href' => 'node/' . $element['#default_value'] . '/edit'
        ),
      );
    }
  }
  return array();
}

function node_reference_dialog_add_link($element, $widget_settings, $field, $instance) {
  $add_links = array();
  foreach ($field['settings']['referenceable_types'] as $type => $active) {
    if ($active !== 0) {
      $node_type = node_type_load($type);
      if (node_access('create', $node_type->name)) {
        $add_links[] = array(
          'title' => t('Create @type', array('@type' => $node_type->name)),
          'href' => 'node/add/' . strtr($type, array('_' => '-')),
        );
      }
    }
  }
  return $add_links;
}

function node_reference_dialog_views_query($display, $view, $instance, $field) {
  // We need to make sure that no entries that we can't add to our field shows
  // up, so we need to limit the data here.
  $types = array();
  foreach ($field['settings']['referenceable_types'] as $type => $active) {
    if ($active !== 0) {
      $types[] = $type;
    }
  }
  $view->query->add_where(0, "$view->base_table.type", $types);
}