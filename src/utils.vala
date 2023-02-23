using Json;

namespace Hacer {
	public class Utils {
		public static int binary_search_json_array(Json.Array array, int64 id) {
			int start = 0;
			int end = (int) array.get_length() - 1;
			while (start <= end) {
				int mid = (start + end) / 2;
				var obj_id = array.get_element(mid).get_object().get_int_member("id");
				// if (obj != null) {
				// int64 obj_id = obj.get_int_member("id");
				if (obj_id == id) {
					return mid;
				} else if (obj_id < id) {
					start = mid + 1;
				} else {
					end = mid - 1;
				}
			}
			return -1;
		}
	}
}