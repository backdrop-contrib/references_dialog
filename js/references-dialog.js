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
      this.open_dialog = $('<iframe class="references-dialog-iframe" src="' + href + '"></iframe>').dialog({
        width: "auto",
        height: "auto",
        autoResize: true,
        modal: true,
        resizable: false,
        position: "top",
        title: $(this).html(),
        close: function() { this.dialog_open = false; }
      }).width(700).height(600);
      this.dialog_open = true;
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
