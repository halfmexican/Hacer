using Gtk, Adw, Pango;
namespace Hacer {
    [GtkTemplate (ui = "/com/github/halfmexican/hacer/agenda_row.ui")]
    public class ActionAgendaRow : Adw.ActionRow{
        [GtkChild] private unowned CheckButton check_button;
        [GtkChild] private unowned Button trash_button;
        [GtkChild] private unowned ToggleButton star_button;
        [GtkChild] private unowned Button edit_button;
        [GtkChild] private unowned EditableLabel edit_label;

        File data_file = File.new_for_path(Environment.get_user_data_dir() + "/tasks.json");
        ListBox parent_list_box;
        string task_name;
        bool starred;
 		bool completed;
        int64 id;
        
        public ActionAgendaRow(string task_name, int64 id ,bool completed, bool starred, ListBox parent_list_box){

            /////Initialization//////
            this.parent_list_box = parent_list_box;
            this.task_name = task_name;
            this.set_title(task_name);
            this.starred = starred;
 			this.completed = completed;
            this.id = id;

            //////Connecting Signals//////
            this.activated.connect(show_edit_button);
            check_button.toggled.connect(complete_task);
            parent_list_box.row_activated.connect(check_selection);
            trash_button.clicked.connect(remove_task);
            star_button.toggled.connect(star_task);
            edit_button.clicked.connect(show_editable_label);

            check_button.set_active(this.completed);
            star_button.set_active(this.starred);
        }

        public void check_selection(ListBoxRow? row){
            if(row != this){
                edit_button.hide();
            }
        }

        public void remove_task(){
            ListBox task_list = this.get_parent() as ListBox;
            task_list.remove(this);
        }

        public void star_task(){
            if(star_button.get_active()){
                star_button.set_icon_name("starred-symbolic");
                star_button.add_css_class("suggested-action");
                starred = true;
            }else{
                star_button.set_icon_name("non-starred-symbolic");
                star_button.remove_css_class("suggested-action");
                starred = false;
            }
        }

        public void show_edit_button(){
            //only shows the button if it's not visible
            if(!edit_button.visible){
                edit_button.show();
            }
            else {
                edit_button.hide();
            }
        }

        public void show_editable_label(){
            this.set_title(" ");
            edit_label.set_text(this.task_name);
            edit_label.show();
            edit_label.grab_focus();
            edit_label.start_editing();

 			//Connect the delegate signal so we know when to update title
 			var gtk_text = edit_label.get_delegate() as Text;
 			gtk_text.activate.connect(change_task_name);
        }

        public void complete_task(){
			//handles the scenario where a user
			//clicks on the check button while editing text
			if(edit_label.visible){
				edit_label.hide();
				this.set_title(task_name);
				this.strikethrough();
				return;
			}

			if(!check_button.get_active()){
				this.set_title(task_name);
			} else {
				this.strikethrough();
				this.completed = true;
			}
        }

        public void change_task_name(){
			edit_label.hide();
			edit_button.hide();
			task_name = edit_label.get_text();

			if(!check_button.get_active()){
				this.set_title(task_name);
			} else {
				this.set_title(task_name);
				this.strikethrough();
			}
        }

        public void strikethrough(){
				this.set_title("<s>" + task_name + "</s>");
		}
    }
}
