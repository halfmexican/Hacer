/* window.vala
 *
 * Copyright 2022-2023 Jose Hunter
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */
using Gtk, Adw, Json;

namespace Hacer {
    [GtkTemplate(ui = "/com/github/halfmexican/hacer/window.ui")]
    public class Window : Adw.ApplicationWindow {
        [GtkChild] unowned Adw.WindowTitle task_window_title;
        [GtkChild] unowned Entry task_entry;
        [GtkChild] unowned ListBox task_list;
        [GtkChild] unowned Button leaflet_forward;
        [GtkChild] unowned Button leaflet_back;
        [GtkChild] unowned Box task_view;
        [GtkChild] unowned Box list_view;
        [GtkChild] unowned ListBox list_box_list;
        [GtkChild] unowned Leaflet adw_leaflet;
        [GtkChild] unowned ActionRow all_tasks_row;
        [GtkChild] unowned ActionRow completed_tasks_row;
        [GtkChild] unowned ActionRow starred_tasks_row;
        [GtkChild] unowned Clamp adw_clamp;
        [GtkChild] unowned Revealer task_label_revealer;

        File data_file = File.new_for_path(Environment.get_user_data_dir() + "/tasks.json");
        Json.Parser parser;
        Json.Array array;
 		Utils utils;
 		uint timeout_id;
        unowned int64 next_id = 0;

        public Window(Gtk.Application app) {
            GLib.Object(application: app);
            //////Connect Signals//////
            task_entry.activate.connect(on_enter_released);
            leaflet_forward.clicked.connect(show_task_view);
            leaflet_back.clicked.connect(show_list_view);
            all_tasks_row.activated.connect(show_all_tasks);
            completed_tasks_row.activated.connect(show_completed_tasks);
            starred_tasks_row.activated.connect(show_starred_tasks);

            /////Initial Set-up//////
            // Default to showing tasks
            adw_leaflet.set_visible_child(task_view);
            // Default to show all tasks at startup
            list_box_list.select_row(all_tasks_row);
            parser = new Json.Parser();
        	utils = new Hacer.Utils();
        
            if (!data_file.query_exists()) {
                print("File '%s' does not exist.\n", data_file.get_path());
                // Create a new file with this name
                // TODOnt: when creating new file use builder to create a blank array
                var file_stream = data_file.create(FileCreateFlags.NONE);
                _init_new_file();
            } else {
                print("File %s referenced\n", data_file.get_path());
            }

            _load_tasks_from_json();

			timeout_id = Timeout.add_full(1, 500, ()=>{
				this._revealer_check();
				return true;});
        }

        public void on_enter_released() {
            string text = this.task_entry.get_text();
            this._entry_add(text);
        }

        public void show_task_view() {
            adw_leaflet.set_visible_child(task_view);
        }

        public void show_list_view() {
            adw_leaflet.set_visible_child(list_view);
        }

         public void show_all_tasks(){
            task_list.invalidate_filter();
            task_list.set_filter_func(all_filter);
        }

        public void show_completed_tasks(){
            task_list.invalidate_filter();
            task_list.set_filter_func(completed_filter);
        }

        public void show_starred_tasks(){
            task_list.invalidate_filter();
            task_list.set_filter_func(starred_filter);
        }

        private bool all_filter(){
            return true;
       }

        private bool completed_filter(Gtk.ListBoxRow row){
            var agenda_row = (AgendaRow) row;

            if(agenda_row.completed)
                return true;

            return false;
        }

        private bool starred_filter(Gtk.ListBoxRow row){
            var agenda_row = row as AgendaRow;

            if(agenda_row.starred)
                return true;

            return false;
       }

        private void _entry_add(string task_name) {
            var agenda_row = new AgendaRow(task_name, next_id, false, false);
            add_task(agenda_row);
            save_task(task_name, next_id, false, false);
            print("New Task: " + task_name + "  id: %s" + "\n", next_id.to_string());
            task_entry.set_text("");
            next_id++;
        }

        // TODO: Make a task Manager Class
        public void save_task(string task_name, int64 id, bool complete, bool starred) {
            try {
                // File Jazz
                FileIOStream iostream = data_file.open_readwrite();
                OutputStream o_stream = iostream.output_stream;
                DataOutputStream do_stream = new DataOutputStream(o_stream);

                // Builds Json Object
                Json.Builder builder = new Json.Builder();
                builder.begin_object();
                {
                    builder.set_member_name("id");
                    builder.add_int_value(id);
                    builder.set_member_name("task_name");
                    builder.add_string_value(task_name);
                    builder.set_member_name("complete");
                    builder.add_boolean_value(complete);
                    builder.set_member_name("starred");
                    builder.add_boolean_value(starred);
                }
                builder.end_object();

                // Get reference to the Object we just made
                Json.Object task_obj = builder.get_root().get_object();

                // We create a Generator to get the data from the builder
                // we create the Parser to get reference to the file
                Json.Generator generator = new Json.Generator() { pretty = true };
                Json.Parser parser = new Json.Parser();

                // Add our Task Object to the Json Array that exists in our file
                parser.load_from_file(data_file.get_path());
                Json.Array array = parser.get_root().get_object().get_array_member("Tasks");
                array.add_object_element(task_obj);

                // Gets the generated Json Tree as a string and write to file
                generator.set_root(parser.get_root());
                string str = generator.to_data(null);
                do_stream.put_string(str);
            } catch (Error e) {
                print(e.message);
            }
        }
        
        public void remove_task(int64 task_id) {
            Json.Parser parser = new Json.Parser();
            // Add our Task Object to the Json Array that exists in our file
            parser.load_from_file(data_file.get_path());
            array = parser.get_root().get_object().get_array_member("Tasks");

            for (int i = 0; i < array.get_length(); ++i) {
                var obj = array.get_element(i).get_object();

                if (obj.get_int_member("id") == task_id) {
                    array.remove_element(i);

                    try {
                        // File Jazz
                        Json.Generator generator = new Json.Generator() { pretty = true };;
                        generator.set_root(parser.get_root());
                        string str = generator.to_data(null);
                        data_file.replace_contents(str.data, null, false, FileCreateFlags.NONE, null);
                    } catch (Error e) {
                        print(e.message);
                    }
                }
            }
        }

        private void update_task_property(int64 task_id, string property_name, Variant property_value) {
            // Load our Task Object to the Json Array that exists in our file
            Json.Parser parser = new Json.Parser();
            parser.load_from_file(data_file.get_path());

            // Get the array of tasks from the JSON data
            array = parser.get_root().get_object().get_array_member("Tasks");

            // Retrieve the object index from the array based on id
            uint obj_index  = Utils.binary_search_json_array(array, task_id);

            // Get the task object and update its specified property
            Json.Object task_obj = array.get_element(obj_index).get_object();
    
            // Check the variant type and set the property accordingly
            if (property_value.is_of_type (VariantType.BOOLEAN)) {
                task_obj.set_boolean_member(property_name, property_value.get_boolean());
            } else if (property_value.is_of_type (VariantType.STRING)) {
                task_obj.set_string_member(property_name, property_value.get_string());
            } else {
                print("Unsupported property type: %s\n", property_value.get_type_string());
                return;
            }

            try {
                // Write updated data back to file
                Json.Generator generator = new Json.Generator() { pretty = true };
                generator.set_root(parser.get_root());
                string str = generator.to_data(null);
                data_file.replace_contents(str.data, null, false, FileCreateFlags.NONE, null);
            } catch (Error e) {
                print("Failed to update task property: " + e.message);
            }
        }

        public void star_task(int64 task_id, bool starred){
            update_task_property(task_id, "starred", new Variant.boolean(starred));
        }

        public void complete_task(int64 task_id, bool complete) {
            update_task_property(task_id, "complete", new Variant.boolean(complete));
        }

        public void change_task_name(int64 task_id, string task_name){
            update_task_property(task_id, "task_name", new Variant.string(task_name));
        }

	    /**
 		    * Adds a Agenda Row to the task_list.
 		    * This method doesn't save the task
 	    */
        public void add_task(AgendaRow agenda_row) {
            task_list.append(agenda_row);

 			// Connecting signals
 			agenda_row.connect_parent_list_box();
            agenda_row.removed_task.connect(remove_task);
 			agenda_row.starred_task.connect(star_task);
 			agenda_row.completed_task.connect(complete_task);
			agenda_row.changed_name.connect(change_task_name);
        }

        private void _load_tasks_from_json() {
           	string task_name = null;
            bool complete = false;
            bool starred = false;
            int64 obj_id = 0;

            // Parsing Json
            Json.Parser parser = new Json.Parser();
            parser.load_from_file(data_file.get_path());
            Json.Object root_object = parser.get_root().get_object();
            Json.Array array = root_object.get_array_member("Tasks");

            foreach (var tasks in array.get_elements()) {
                Json.Object obj = tasks.get_object();
                foreach (var members in obj.get_members()) {
                    switch (members) {
                    case "id":
                        obj_id = obj.get_int_member("id");
                        // always set next id to the current highest plus 1
                        if (next_id < obj_id)
                            next_id = (1 + obj_id);
                        break;
                    case "task_name":
 						task_name = obj.get_string_member("task_name"); ;
 						break;
                    case "complete":
                        complete = obj.get_boolean_member("complete");
                        break;
                    case "starred":
                        starred = obj.get_boolean_member("starred");
                        break;
                    }
                }

                var agenda_row = new AgendaRow(task_name, obj_id, complete, starred);
                add_task(agenda_row);
            }
        }

        private void _init_new_file() {
			// Builds Json Object
			string file_template = """{"Tasks" : []}""";
          	data_file.replace_contents(file_template.data, null, false, FileCreateFlags.NONE, null);
 			print("New file Created at %s from template\n", data_file.get_path());
        }
        
        //TODO: Actually dynamicly set title
        private void _revealer_check(){
			int height = this.get_allocated_height();
			if(height > 620){
				task_label_revealer.set_reveal_child(true);
				task_window_title.set_title("Hacer");

			} else {
				task_label_revealer.set_reveal_child(false);
			    task_window_title.set_title("Tasks");
			}
		}
    }
}