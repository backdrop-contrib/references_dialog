(function ($) {

/**
 * Attach the child dialog behavior to new content.
 */
Drupal.behaviors.referencesDialogChild = {
  attach: function(context, settings) {
    var entity_id = parseInt(settings.ReferencesDialog.entity_id);
    var title = settings.ReferencesDialog.title;
    if (entity_id != null && entity_id != 0) {
      parent.Drupal.ReferencesDialog.close(entity_id, title);
    }
  }
}
})(jQuery);
