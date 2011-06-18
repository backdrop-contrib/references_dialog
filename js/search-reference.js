(function ($) {
  Drupal.behaviors.referencesDialog = {
    attach: function (context, settings) {
      // Check what type of display we are dealing with.
      // We can't combine all of these, since that causes
      // JQuery.each() to freak ut.'
      var selector = null;
      if ($('table.views-table').size() > 0) {
        selector = $('table.views-table tbody tr');
      }
      else if ($('table.views-view-grid').size() > 0) {
        selector = $('table.views-view-grid td');
      }
      else if ($('.views-row').size() > 0) {
        selector = $('.views-row');
      }
      else {
        return;
      }
      selector.each(function(index) {
        $(this).click(function() {
          // Fetch the entity from wherever it might be.
          var entity = settings.ReferencesDialog.entities[index];
          // Tell our parent that we are done with what we want to do here.
          parent.Drupal.ReferencesDialog.close(entity.entity_id, entity.title);
          return false;
        });
      });
    }
  }
})(jQuery);