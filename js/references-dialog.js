(function ($) {
  Drupal.behaviors.referencesDialog = {
    attach: function (context, settings) {
      $('.references-dialog-activate').click(function() {
        Drupal.ReferencesDialog.open($(this).attr('href'));
        var reference_element = $(this).parent().find('input');
        Drupal.ReferencesDialog.entityIdReceived = function(entity_id, title) {
          reference_element.val(title + ' [nid:' + entity_id + ']');
        }
        return false;
      }, context);
    }
  };
  Drupal.ReferencesDialog = {
    dialog_open: false,
    open_dialog: null
  }
  
  Drupal.ReferencesDialog.entityIdReceived = null;
  /**
   * Open a dialog window.
   */
  Drupal.ReferencesDialog.open = function(href) {
    if (!this.dialog_open) {
      href += "?render=references-dialog";
      // Get the current window size and do 75% of the width and 90% of the height.
      var window_width = $(window).width() / 100*75;
      var window_height = $(window).height() / 100*90;
      this.open_dialog = $('<iframe class="references-dialog-iframe" src="' + href + '"></iframe>').dialog({
        width: window_width,
        height: window_height,
        modal: true,
        resizable: false,
        position: ["center", 10],
        title: $(this).html(),
        close: function() { Drupal.ReferencesDialog.dialog_open = false; }
      }).width(window_width-10).height(window_height)
      $(window).bind("resize scroll", function() {
        // Move the dialog the main window moves.
        if (typeof Drupal.ReferencesDialog == "object") {
          Drupal.ReferencesDialog.open_dialog.
            dialog("option", "position", ["center", 10]);
          Drupal.ReferencesDialog.setDimensions();
        }
      });
      this.dialog_open = true;
    }
  }
  
  Drupal.ReferencesDialog.setDimensions = function() {
    if (typeof Drupal.ReferencesDialog == "object") {
      var window_width = $(window).width() / 100*75;
      var window_height = $(window).height() / 100*90;
      this.open_dialog.
        dialog("option", "width", window_width).
        dialog("option", "height", window_height).
        width(window_width-10).height(window_height);
    }
  }
  Drupal.ReferencesDialog.close = function(entity_id, title) {
    this.open_dialog.dialog('close');
    this.open_dialog.dialog('destroy');
    this.open_dialog = null;
    this.dialog_open = false;
    if (typeof this.entityIdReceived == "function") {
      this.entityIdReceived(entity_id, title);
    }
  }
}(jQuery));
