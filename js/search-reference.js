(function ($) {
  Drupal.behaviors.referencesDialog = {
    attach: function (context, settings) {
      $('.views-row').click(function() {
        // Get the current id.
        $('.views-row').css('display', 'block');
        var classes = $(this).attr('class');
        var views_row_regexp = /views-row-([0-9]+)/
        var row = parseInt(views_row_regexp.exec(classes)[1]-1);
        var entity = settings.ReferencesDialog.entities[row];
        parent.Drupal.ReferencesDialog.close(entity.entity_id, entity.title);
      });
    }
  }
})(jQuery);