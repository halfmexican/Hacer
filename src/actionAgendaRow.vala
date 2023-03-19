using Gtk, Adw, Pango;
namespace Hacer {
    [GtkTemplate(ui = "/com/github/halfmexican/hacer/agenda_row.ui")]
    public class ActionAgendaRow : Adw.ActionRow {
        [GtkChild] private unowned CheckButton check_button;
        [GtkChild] private unowned Button trash_button;
        [GtkChild] private unowned ToggleButton star_button;
        [GtkChild] private unowned Button edit_button;
        [GtkChild] private unowned EditableLabel edit_label;
        [GtkChild] private unowned Image drag_handle;

        File data_file = File.new_for_path(Environment.get_user_data_dir() + "/tasks.json");
        ListBox parent_list_box;
        Json.Parser parser;
        string task_name;
        // TODO: getter and setter
        public bool starred;
        public bool completed;
        public int64 id;
        private int _drag_x;
        private int _drag_y;

        public signal void removed_task(int64 id);
        public signal void starred_task(int64 id, bool starred);
        public signal void completed_task(int64 id, bool completed);
        public signal void changed_name(int64 id, string name);

        public ActionAgendaRow(string task_name, int64 id, bool completed, bool starred) {

            /////Initialization//////
            this.task_name = task_name;
            this.set_title(task_name);
            this.edit_label.set_text(this.task_name);
            this.starred = starred;
            this.completed = completed;
            this.id = id;
            parser = new Json.Parser();

            //////Connecting Signals//////
            this.activated.connect(show_editable_label);
            check_button.toggled.connect(complete_task);
            trash_button.clicked.connect(remove_task);
            star_button.toggled.connect(star_task);
            edit_button.clicked.connect(show_editable_label);
            check_button.set_active(this.completed);
            star_button.set_active(this.starred);

            //////Drag and Drop//////
            var drag = new Gtk.DragSource();
            this.add_controller(drag);

            drag.prepare.connect ((_x, _y) => {
                _drag_x = (int) _x;
                _drag_y = (int) _y;

                Value val = Value (typeof (ActionAgendaRow));
                val.set_object (this);
                return new Gdk.ContentProvider.for_value (val);
            });

            drag.drag_begin.connect ((drag) => {
                Gtk.Allocation allocation;
                this.get_allocation (out allocation);
                parent_list_box.drag_highlight_row (this);
                parent_list_box.remove(this);
                this.set_size_request (allocation.width, allocation.height);
                this.set_state_flags (Gtk.StateFlags.DROP_ACTIVE, false);
                var drag_icon = (Gtk.DragIcon) Gtk.DragIcon.get_for_drag (drag);
                this.add_css_class("agenda-row-hovering");
                this.remove_css_class("agenda-row");
                drag_icon.child = this;
                drag.set_hotspot (_drag_x, _drag_y);
            });

            // drop controller
            var drop = new Gtk.DropTarget (typeof (ActionAgendaRow), Gdk.DragAction.COPY);
            this.add_controller (drop);
            drop.drop.connect ((val, _x, _y) => {
                return drop_handler(val, _x, _y, this);
            });

            var drop_motion = new Gtk.DropControllerMotion();
            this.add_controller(drop_motion);

            drop_motion.enter.connect ((_x, _y) => {
                this.add_css_class("agenda-row-drop");
                this.remove_css_class("agenda-row");
            });

            drop_motion.leave.connect (() => {
                this.remove_css_class("agenda-row-drop");
                this.add_css_class("agenda-row");
            });

        }

        private bool drop_handler(Value val, double x, double y, ActionAgendaRow target_row) {
            if (!val.holds (typeof (ActionAgendaRow))) return false;
                int index = target_row.get_index();
                ActionAgendaRow row = val.get_object() as ActionAgendaRow;
                var icon = row.parent;
                row.unparent();
                row.remove_css_class("agenda-row-hovering");
                target_row.remove_css_class("agenda-row-drop");
                target_row.add_css_class("agenda-row");
                row.add_css_class("agenda-row");
                icon.dispose();
                parent_list_box.insert(row, index);
            return true;
        }


        public void connect_parent_list_box() {
            this.parent_list_box = this.get_parent() as ListBox;
            this.parent_list_box.row_activated.connect(check_selection);
        }

        public void check_selection(ListBoxRow? row) {
            if (row != this) {
                change_task_name();
            }
        }

        public void remove_task() {
            this.removed_task(this.id);
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
            this.starred_task(this.id, this.starred);
        }

        public void show_editable_label() {
            this.add_css_class("agenda-row-editing");
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

            this.completed_task(this.id, this.completed);
        }

        public void change_task_name() {
            this.remove_css_class("agenda-row-editing");
            edit_label.hide();
            edit_button.hide();
            task_name = Markup.escape_text(edit_label.get_text());
            this.changed_name(id, task_name);
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
