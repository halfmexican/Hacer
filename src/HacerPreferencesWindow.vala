using Gtk, Adw, GLib;
namespace Hacer {
    [GtkTemplate(ui = "/com/github/halfmexican/hacer/prefs.ui")]
    public class PreferencesWindow : Adw.PreferencesWindow {

    
        [GtkChild] private unowned Gtk.Switch circular_checkboxes_switch;

        public PreferencesWindow() {
            Hacer.Window hacer_window = this.transient_for as Hacer.Window;

            // Binding
            Application.settings.bind("use-circular-checkboxes", circular_checkboxes_switch, "active", SettingsBindFlags.DEFAULT);
        }
    }
}
