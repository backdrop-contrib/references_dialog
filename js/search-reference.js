(function ($) {
  Backdrop.behaviors.referencesDialog = {
    attach: function (context, settings) {
      // Check what type of display we are dealing with.
      // We can't combine all of these, since that causes
      // JQuery.each() to freak ut.'
      var selector = null;
      // Check for elements matching any of the desired selectors.
      if ($('table.views-table', context).length > 0) {
        // Use the views-table if found.
        selector = $('table.views-table tbody tr:not(.views-table-row-select-all)', context);
      }
      else if ($('table.views-view-grid', context).length > 0) {
        // Use views-view-grid if found.
        selector = $('table.views-view-grid td', context);
      }
      else if ($('.views-row', context).length > 0) {
        // Use views-row if found.
        selector = $('.views-row', context);
      }
      else {
        // If no elements match any of the selectors, exit.
        return;
      }
      selector.each(function(index) {
        $(this).click(function(e) {
          e.preventDefault();
          // Ignore if the element is a link.
          if (e.target && e.target.nodeName && e.target.nodeName.toLowerCase() !== 'a') {
            // Fetch the entity from wherever it might be.
            var entity = settings.ReferencesDialog.entities[index];
            // Tell our parent that we are done with what we want to do here.
            parent.Backdrop.ReferencesDialog.close(entity.entity_type, entity.entity_id, entity.title);
          }
        });
      });
      // Process links so that they have the render=references_dialog
      // parameter. Also, make sure that we don't close the dialog and enter
      // anything upon entity submittion.'
      $('#references-dialog-page a').once('search-reference-links', function(key, element) {

        var href = $(element).attr('href');

        // For links within the Views table, or those with a destination
        // parameter, open in a new window instead.
        if (href.indexOf('destination=') >= 0 || $(element).parents('table.views-table tbody').length > 0) {
          $(element).attr('target', '_blank');
          return;
        }

        // Don't modify JavaScript URLs or anchors.
        if (href.indexOf('#') >= 0 || href.indexOf('javascript:') == 0) {
          return;
        }

        $(element).attr('href', href + (href.indexOf('?') >= 0 ? '&' : '?')
          + 'render=references-dialog&closeonsubmit=0');
      })
    }
  }
})(jQuery);
