#ifndef JSON_HELPER_H_
#define JSON_HELPER_H_

#include <iostream>
#include <string>
#include <picojson.h>
#include <vector>

using std::vector;

namespace csci3081 {

class JsonHelper {
public:

  /********************** Querying functions **************************/
  /**
   * USAGE: Use these querying methods to retrieve entity details from a json object.
   * Look at project/web/scenes/umn.json lines 5-18 for an example of how an entity is represeted in
   * a json object, or use JsonHelper::PrintEntityDetails(const picojson::object& val) to print the
   * object's contents to the terminal.
   *
   * Examples:
   *
   * `vector<float> position = JsonHelper::GetStdFloatVector(val, "position");`
   *
   * `string type = JsonHelper::GetString(val, "type");`
   *
   * ```
   * bool contains = JsonHelper::ContainsKey(val, "battery_capacity");
   * if (contains)...
   * ```
   *
   * ```
   * std::vector<std::vector<float>> path = ...
   * ...
   * picojson::object notification_builder = JsonHelper::CreateJsonNotification();
   * JsonHelper::AddStdVectorVectorFloatToObject(notification_builder, "path", path);
   * ...
   * picojson::value notification_to_send = JsonHelper::ConvertJsonObjectToValue(notification_builder);
   * SendToObservers(notification_to_send);
   * ...
   * ```
   */

  /// Returns the key from json object obj as a json value, throws error if key doesn't exist.
  static const picojson::value& GetValue(const picojson::object& obj, std::string key) {
    if (!JsonHelper::ContainsKey(obj, key)) {
      throw std::logic_error("Trying to get the picojson::value from key that does not exist: " + key);
    }
    return obj.find(key)->second;
  }

  /// Returns the key from json object obj as a json object, throws error if key doesn't exist.
  static const picojson::object& GetObject(const picojson::object& obj, std::string key) {
    if (!JsonHelper::ContainsKey(obj, key)) {
      throw std::logic_error("Trying to get the picojson::object from key that does not exist: " + key);
    }
      return GetValue(obj, key).get<picojson::object>();
  }

  /// Returns the key from json object obj as a json array, will throw an error if key doesn't exist.
  static const picojson::array& GetArray(const picojson::object& obj, std::string key) {
    if (!JsonHelper::ContainsKey(obj, key)) {
      throw std::logic_error("Trying to get the picojson::array from key that does not exist: " + key);
    }
      return GetValue(obj, key).get<picojson::array>();
  }

  /// Returns the key from json object obj as a string, will throw an error if key doesn't exist.
  static std::string GetString(const picojson::object& obj, std::string key) {
    if (!JsonHelper::ContainsKey(obj, key)) {
      throw std::logic_error("Trying to get the string from key that does not exist: " + key);
    }
      return GetValue(obj, key).get<std::string>();
  }

  /// Returns the key from json object obj as a double, will throw an error if key doesn't exist.
  static double GetDouble(const picojson::object& obj, std::string key) {
    if (!JsonHelper::ContainsKey(obj, key)) {
      throw std::logic_error("Trying to get the double from key that does not exist: " + key);
    }
    return GetValue(obj, key).get<double>();
  }

  /// Returns the key from json object obj as a float vector, will throw an error if key doesn't exist.
  static std::vector<float> GetStdFloatVector(const picojson::object& obj, std::string key) {
    if (!JsonHelper::ContainsKey(obj, key)) {
      throw std::logic_error("Trying to get the std::vector<float> from key that does not exist: " + key);
    }
    std::vector<float> vec;
    picojson::array arr = GetArray(obj, key);
    for (int i = 0; i < arr.size(); i++) {
      vec.push_back(arr[i].get<double>());
    }
    return vec;
  }

  /// Returns a boolean value of whether the json object obj contains key or not
  static bool ContainsKey(const picojson::object& obj, std::string key) {
    return obj.find(key) != obj.end();
  }

  /********************** Creation functions **************************/
  
  /// Create a new json object for sending notifications
  static picojson::object CreateJsonNotification() {
    picojson::object obj;
    AddStringToJsonObject(obj, "type", "notify");
    return obj;
  }

  /// Returns a new json object.
  static picojson::object CreateJsonObject() {
    return picojson::object();
  }

  /// Converts given obj to an equivalent picojson::value
  static picojson::value ConvertPicojsonObjectToValue(picojson::object& obj) {
    return picojson::value(obj);
  }

  /// Adds a picojson value to the specifiied key in a json object
  static void AddValueToJsonObject(picojson::object& obj, std::string key, picojson::value val) {
    obj[key] = val;
  }

  /// Adds the latter picojson object to the former object as a value under the key 'key'
  static void AddObjectToJsonObject(picojson::object& obj, std::string key, picojson::object& val) {
    obj[key] = JsonHelper::ConvertPicojsonObjectToValue(val);
  }

  /// Adds a string value named key to a json object.
  static void AddStringToJsonObject(picojson::object& obj, std::string key, std::string val) {
    obj[key] = picojson::value(val);
  }

  /// Adds a float value named key to a json object.
  static void AddFloatToJsonObject(picojson::object& obj, std::string key, float num) {
    obj[key] = picojson::value(num);
  }

  /// Adds a float vector value named key to a json object
  static void AddStdFloatVectorToJsonObject(picojson::object& obj, std::string key, std::vector<float> vec) {
    picojson::array arr = CreateJsonArrayFromVector(vec);
    obj[key] = picojson::value(arr);
  }

  /// Creates a json array from a float vector.
  static picojson::array CreateJsonArrayFromVector(std::vector<float> vec) {
    picojson::array arr;
    for (auto num : vec) {
      arr.push_back(picojson::value(num));
    }
    return arr;
  }

  /// Given a picojson object, key, and vector<vector<float>> array, adds the array as the value for key in obj
  static void AddStdVectorVectorFloatToJsonObject(picojson::object& obj, 
                                                 std::string key, std::vector<std::vector<float>> array) {
    obj[key] = EncodeArray(array);
  }

  /// Given a vector<vector<float>> array, returns the array as a picojson::value
  static picojson::value EncodeArray(const vector<vector<float>> arr) { //todo discard some precision by converting to strings?
    vector<picojson::value> result;
    for(vector<float> subarr : arr) {
      vector<picojson::value> subarr_encode;
      for(float val : subarr) {
        subarr_encode.push_back(picojson::value(val));
      }
      result.push_back(picojson::value(subarr_encode));
    }
    return picojson::value(result);
  }


  /********************** Printing functions **************************/

  /// Helper method for PrintEntityDetails.
  static void PrintArray(const picojson::array& arr) {
    std::cout << "Printing Array:" << std::endl << std::endl;
    int i = 0;
    for (auto key : arr) {
      std::cout << "Array item: " << i++ << std::endl;
      std::cout << "    " << key << std::endl;
    }
  }

  /// Helper method for PrintEntityDetails.
  static void PrintKeyValues(const picojson::object& obj, std::string prefix = "  ") {
    std::cout << "PrintKeyValues ---------" << std::endl;
      for (picojson::object::const_iterator it = obj.begin(); it != obj.end(); it++) {
        std::cout << prefix << it->first << ": " << it->second << std::endl;
      }
    std::cout << "End PrintKeyValues ---------" << std::endl;
  }

  /// Helper method for PrintEntityDetails.
  static void Print(const picojson::object& obj, std::string prefix = "  ") {
    picojson::value val(obj);
    std::cout << prefix << val.serialize() << std::endl;
  }

  /// Prints the details of a json object representation of an entity.
  static void PrintEntityDetails(const picojson::object& val) {
    std::cout << "\n------JSON:------" << std::endl;
    JsonHelper::Print(val);

    std::cout << "------Key Values:------" << std::endl;
    JsonHelper::PrintKeyValues(val);

    std::cout << "------Entity Type:------" << std::endl;
    std::string type = JsonHelper::GetString(val, "type");
    std::cout << "  " << type << std::endl;

    std::cout << "------Contains Key:------" << std::endl;
    std::cout << "  Contains type: " << JsonHelper::ContainsKey(val, "type") << std::endl;
    std::cout << "  Contains otherKey: " << JsonHelper::ContainsKey(val, "otherKey") << std::endl;
    std::cout << "  Contains position: " << JsonHelper::ContainsKey(val, "position") << std::endl;

    std::cout << "------Position array:------" << std::endl;
    if (JsonHelper::ContainsKey(val, "position")) {
      const picojson::array& position = JsonHelper::GetArray(val, "position");
      for (int f = 0; f < position.size(); f++) {
        std::cout << "  position[" << f << "]: " << position[f] << std::endl;
      }
    }
    std::cout << std::endl;
  }
};

}  // namespace csci3081
#endif
