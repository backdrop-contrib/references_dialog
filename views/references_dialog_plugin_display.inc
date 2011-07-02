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
  
  function uses_exposed() {
    return TRUE;
  }

  /**
   * Override references_plugin_display, and
   * allow for other style types.
   */
  function get_style_type() { return 'normal'; }

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
    // Let the world know that this is the page view we're using.
    views_set_page_view($this->view);
    // Prior to this being called, the $view should already be set to this
    // display, and arguments should be set on the view.
    $this->view->build();
    if (!empty($this->view->build_info['fail'])) {
      return drupal_not_found();
    }

    $this->view->get_breadcrumb(TRUE);

    // And the title, which is much easier.
    drupal_set_title(filter_xss_admin($this->view->get_title()), PASS_THROUGH);
    // Let's add the data necessary to javascript, so that we can
    // act upon it there.
    $js_result = array();
    foreach ($this->view->result as $result) {
      $js_result[] = array('entity_id' => $result->{$this->view->base_field}, 'title' => $result->node_title);
    }
    drupal_add_js(drupal_get_path('module', 'references_dialog') . '/js/search-reference.js');
    drupal_add_js(array('ReferencesDialog' => array('entities' => $js_result)), 'setting');

    // And now render the view.
    return $this->view->render();
  }
  
  function query() {
    // At this point we need to see if our widget needs to inject something
    // into the query in order to filter out unwanted data.
    if (isset($this->view->references_dialog['instance'])) {
      $widget_type = $this->view->references_dialog['instance']['widget']['type'];
      $dialog_widget = references_dialog_widget_load($widget_type);
      if (isset($dialog_widget['views_query']) && function_exists($dialog_widget['views_query'])) {
        $dialog_widget['views_query']($this, $this->view, $this->view->references_dialog['instance'], $this->view->references_dialog['field']);
      }
    }
  }
  
  function render() {
    return theme($this->theme_functions(), array('view' => $this->view));
  }
}