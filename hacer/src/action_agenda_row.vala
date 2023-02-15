using Gtk, Adw, Pango;
namespace Hacer {
    [GtkTemplate(ui = "/com/github/halfmexican/hacer/agenda_row.ui")]
    public class ActionAgendaRow : Adw.ActionRow {
        [GtkChild] private unowned CheckButton check_button;
        [GtkChild] private unowned Button trash_button;
        [GtkChild] private unowned ToggleButton star_button;
        [GtkChild] private unowned Button edit_button;
        [GtkChild] private unowned EditableLabel edit_label;

        File data_file = File.new_for_path(Environment.get_user_data_dir() + "/tasks.json");
        ListBox parent_list_box;
        Json.Parser parser;
        string task_name;
        bool starred;
        bool completed;
        int64 id;

        public signal void removetask(int64 id);
 		public signal void startask(int64 id, bool starred);
 		public signal void completetask(int64 id, bool completed);

        public ActionAgendaRow(string task_name, int64 id, bool completed, bool starred) {

            /////Initialization//////
            this.parent_list_box;
            this.task_name = task_name;
            this.set_title(task_name);
            this.starred = starred;
            this.completed = completed;
            this.id = id;
            parser = new Json.Parser();

            //////Connecting Signals//////
            this.activated.connect(show_edit_button);
            check_button.toggled.connect(complete_task);
            trash_button.clicked.connect(remove_task);
            star_button.toggled.connect(star_task);
            edit_button.clicked.connect(show_editable_label);
            check_button.set_active(this.completed);
            star_button.set_active(this.starred);
        }

        public void connect_parent_list_box() {
            this.parent_list_box = this.get_parent() as ListBox;
            this.parent_list_box.row_activated.connect(check_selection);
        }

        public void check_selection(ListBoxRow? row) {
            if (row != this) {
                edit_button.hide();
            }
        }

        public void remove_task() {

            this.removetask(this.id);
            ListBox task_list = this.get_parent() as ListBox;
            task_list.remove(this);
            // window.remove_task_id(this.id);
        }

        public void star_task() {
            if (star_button.get_active()) {
                star_button.set_icon_name("starred-symbolic");
                star_button.add_css_class("suggested-action");
                starred = true;
            } else {
                star_button.set_icon_name("non-starred-symbolic");
                star_button.remove_css_class("suggested-action");
                starred = false;
            }
            
            this.startask(this.id, this.starred);
            
        }

        public void show_edit_button() {
            // only shows the button if it's not visible
            if (!edit_button.visible) {
                edit_button.show();
            } else {
                edit_button.hide();
            }
        }

        public void show_editable_label() {
            this.set_title(" ");
            string unescaped_title = this.task_name.replace("&amp;", "&")
                 .replace("&lt;", "<")
                 .replace("&gt;", ">")
                 .replace("&quot;", "\"")
                 .replace("&apos;", "\'");


            edit_label.set_text(unescaped_title);
            edit_label.show();
            edit_label.grab_focus();
            edit_label.start_editing();

            // Connect the delegate signal so we know when to update title
            var gtk_text = edit_label.get_delegate() as Text;
            gtk_text.activate.connect(change_task_name);
        }

        public void complete_task() {
            // handles the scenario where a user
            // clicks on the check button while editing text
            if (edit_label.visible) {
                edit_label.hide();
                this.set_title(task_name);
                this.strikethrough();
                return;
            }

            if (!check_button.get_active()) {
                this.set_title(task_name);
 				this.completed = false;
            } else {
                this.strikethrough();
                this.completed = true;
            }
            
            this.completetask(this.id, this.completed);
        }

		//TODO: Make this save the new name
        public void change_task_name() {
            edit_label.hide();
            edit_button.hide();
            task_name = Markup.escape_text(edit_label.get_text());

            if (!check_button.get_active()) {
                this.set_title(task_name);
            } else {
                this.set_title(task_name);
                this.strikethrough();
            }
        }

        public void strikethrough() {
            this.set_title("<s>" + task_name + "</s>");
        }
    }
}
