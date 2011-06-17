<?php
/**
 * @file
 * Contains the default display plugin.
 */

/**
 * A plugin to handle defaults on a view.
 *
 * @ingroup views_display_plugins
 */
class references_dialog_plugin_display extends references_plugin_display {
  function option_definition() {
    $options = parent::option_definition();

    // Allow the use of any style plugin.
    unset($options['style_plugin']['default']);
    $options['defaults']['default']['style_plugin'] = TRUE;
    $options['defaults']['default']['style_options'] = FALSE;
    $options['row_plugin']['default'] = 'fields';
    $options['defaults']['default']['row_plugin'] = FALSE;
    $options['defaults']['default']['row_options'] = FALSE;

    // Set the display title to an empty string (not used in this display type).
    $options['title']['default'] = '';
    $options['defaults']['default']['title'] = FALSE;

    return $options;
  }
  
  function execute_hook_menu($callbacks) {
    $items = array();
    $items['references/search/%references_dialog_search_view'] = array(
      'type' => MENU_CALLBACK,
      'page callback' => 'references_dialog_search_view',
      'page arguments' => array(2,3),
      'access callback' => 'user_access',
      'access arguments' => array('administer views'),
    );
    return $items;
  }
  
  /**
   * The default execute handler fully renders the view.
   *
   * For the simplest use:
   * @code
   *   $output = $view->execute_display('default', $args);
   * @endcode
   *
   * For more complex usages, a view can be partially built:
   * @code
   *   $view->set_arguments($args);
   *   $view->build('default'); // Build the query
   *   $view->execute(); // Run the query
   *   $output = $view->render(); // Render the view
   * @endcode
   *
   * If short circuited at any point, look in $view->build_info for
   * information about the query. After execute, look in $view->result
   * for the array of objects returned from db_query.
   *
   * You can also do:
   * @code
   *   $view->set_arguments($args);
   *   $output = $view->render('default'); // Render the view
   * @endcode
   *
   * This illustrates that render is smart enough to call build and execute
   * if these items have not already been accomplished.
   *
   * Note that execute also must accomplish other tasks, such
   * as setting page titles, breadcrumbs, and generating exposed filter
   * data if necessary.
   */
  function execute() {
    $output = parent::execute();
    // Let's add the data necessary to javascript, so that we can
    // act upon it there.
    $js_result = array();
    foreach ($this->view->result as $result) {
      $js_result[] = array('entity_id' => $result->{$this->view->base_field}, 'title' => $result->node_title);
    }
    drupal_add_css(drupal_get_path('module', 'references_dialog') . '/css/references_dialog.css');
    drupal_add_js(drupal_get_path('module', 'references_dialog') . '/js/search-reference.js');
    drupal_add_js(array('ReferencesDialog' => array('entities' => $js_result)), 'setting');
    return $output;
  }
}