(function ($) {
  Drupal.behaviors.referencesDialog = {
    attach: function (context, settings) {
      $('.views-row, .views-view-grid td').click(function() {
        var classes = $(this).attr('class');
        // Find out the row number if this is a grid.
        var row = null;
        if ($('#references-dialog-page > .views-view-grid').size() > 0) {
          var col = parseInt(/col-([0-9]+)/.exec(classes)[1]);
          row =  parseInt(/row-([0-9]+)/.exec($(this).parent().attr('class'))[1]) * col - 1;
        }
        else {
          row = parseInt(/views-row-([0-9]+)/.exec(classes)[1] - 1);
        }
        if (typeof row != "null") {
          var entity = settings.ReferencesDialog.entities[row];
          parent.Drupal.ReferencesDialog.close(entity.entity_id, entity.title);
        }
      });
    }
  }
})(jQuery);