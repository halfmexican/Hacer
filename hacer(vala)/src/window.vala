/* window.vala
 *
 * Copyright 2022 Jose Hunter
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
    [GtkTemplate (ui = "/com/github/halfmexican/hacer/window.ui")]
    public class Window : Adw.ApplicationWindow {

        [GtkChild]unowned Entry task_entry;
        [GtkChild]unowned ListBox task_list;
        [GtkChild]unowned Button leaflet_forward;
        [GtkChild]unowned Button leaflet_back;
        [GtkChild]unowned Box task_view;
        [GtkChild]unowned Box list_view;
        [GtkChild]unowned ListBox list_box_list;
        [GtkChild]unowned Leaflet adw_leaflet;
        [GtkChild]unowned ActionRow all_tasks_row;
 		//[GtkChild]unowned ActionRow completed_tasks_row;
 		//[GtkChild]unowned ActionRow starred_tasks_row;
        //[GtkChild]unowned Clamp adw_clamp;

        public Window (Gtk.Application app) {
            GLib.Object (application: app);
            //////Connect Signals//////
            task_entry.activate.connect(on_enter_released);
            leaflet_forward.clicked.connect(show_task_view);
            leaflet_back.clicked.connect(show_list_view);
            all_tasks_row.activated.connect(show_all_tasks);
            /////Initial Set-up//////
            //Default to showing tasks
            adw_leaflet.set_visible_child(task_view);
 			//Default to show all tasks at startup
            list_box_list.select_row(list_box_list.get_row_at_index(0));
            _load_task_from_json();
        }

        public void on_enter_released(){
            string text = this.task_entry.get_text();
            this._entry_add(text);
        }

        public void show_task_view(){
            adw_leaflet.set_visible_child(task_view);
        }

        public void show_list_view(){
            adw_leaflet.set_visible_child(list_view);
        }

        private void _entry_add(string task_name){
            print("New Task: "+ task_name + "\n");
            var agenda_row = new ActionAgendaRow(task_name, false, false, task_list);
            task_list.append(agenda_row);
            task_entry.set_text("");
 			add_task(task_name, false, false);
        }

        public void add_task(string task_name, bool complete, bool starred){
			try {
				//Get the file interface
				File file = File.new_for_path(Environment.get_user_data_dir() + "/tasks.json");

				// File Jazz
				FileIOStream iostream = file.open_readwrite();
				OutputStream o_stream = iostream.output_stream;
				DataOutputStream do_stream = new DataOutputStream(o_stream);

				//Builds Json Object
				Json.Builder builder = new Json.Builder();
				builder.begin_object();
				{
					builder.set_member_name("task_name");
					builder.add_string_value(task_name);
					builder.set_member_name("complete");
					builder.add_boolean_value(complete);
					builder.set_member_name("starred");
					builder.add_boolean_value(starred);
				}
				builder.end_object();

				//Give Reference for the Object we just made
				Json.Object task_obj = builder.get_root().get_object();

				//We create a Generator to get the data from the builder
				//we create the Parser to get reference to the file
				Json.Generator generator = new Json.Generator(){pretty = true};
				Json.Parser parser = new Json.Parser();

				//Add our Task Object to the Json Array that exists in our file
				parser.load_from_file(Environment.get_user_data_dir() + "/tasks.json");
 				Json.Array array = parser.get_root().get_object().get_array_member("Tasks");
				array.add_object_element(task_obj);

				//Gets the generated Json Tree as a string and write to file
				generator.set_root(parser.get_root());
				string str = generator.to_data(null);
				do_stream.put_string(str);
			}
			catch (Error e){
				print(e.message);
			}
		}

        public void show_all_tasks(){
 			//_load_task_from_json();
        }

        private void _load_task_from_json(){
            unowned string task_name = null;
            unowned bool complete = false;
            unowned bool starred = false;

			// Create a file that can only be accessed by the current user:
            File file = File.new_for_path(Environment.get_user_data_dir() + "/tasks.json");

			if(!file.query_exists()){
				print("File '%s' does not exist.", file.get_path());
				// Create a new file with this name
            	var file_stream = file.create (FileCreateFlags.NONE);
			}
			else {
				print("File %s created", file.get_path());
			}

            //Don't fucking ask me
			Json.Parser parser = new Json.Parser();
            parser.load_from_file(file.get_path());
            Json.Object root_object = parser.get_root().get_object();
            Json.Array array = root_object.get_array_member("Tasks");

            foreach(var tasks in array.get_elements()){
                Json.Object obj = tasks.get_object();
                foreach (var members in obj.get_members()){
                    switch (members){
                        case "task_name":
                            task_name = obj.get_string_member("task_name");
                            break;
                        case "complete":
                            complete = obj.get_boolean_member("complete");
                            break;
                        case "starred":
                            starred = obj.get_boolean_member("starred");
                            break;
                  		}
                }

                var item_row = new ActionAgendaRow(task_name, complete, starred, task_list);
                task_list.append(item_row);
            }
        }
    }
}

