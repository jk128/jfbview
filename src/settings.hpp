/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 *  Copyright (C) 2020-2020 Chuan Ji                                         *
 *                                                                           *
 *  Licensed under the Apache License, Version 2.0 (the "License");          *
 *  you may not use this file except in compliance with the License.         *
 *  You may obtain a copy of the License at                                  *
 *                                                                           *
 *   http://www.apache.org/licenses/LICENSE-2.0                              *
 *                                                                           *
 *  Unless required by applicable law or agreed to in writing, software      *
 *  distributed under the License is distributed on an "AS IS" BASIS,        *
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. *
 *  See the License for the specific language governing permissions and      *
 *  limitations under the License.                                           *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

// This file declares the Settings class, which manages this app's persistent
// settings.

#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <string>
#include <unordered_map>

#include "rapidjson/document.h"

// Default config. This is generated during the build process from
// "default_config.json" by "generate_default_config_cpp.cpp".
extern const char* DEFAULT_CONFIG_JSON;

class Settings {
 public:
  // Default JSON parsing flags. We want to be generally permissive with
  // settings files as they are hand edited.
  enum {
    PERMISSIVE_JSON_PARSE_FLAGS =
        rapidjson::kParseCommentsFlag | rapidjson::kParseTrailingCommasFlag |
        rapidjson::kParseEscapedApostropheFlag |
        rapidjson::kParseNanAndInfFlag | rapidjson::kParseStopWhenDoneFlag
  };

  // Factory method to create and initialize a Settings instance.
  // config_file_path and history_file_path will fall back to their respective
  // defaults if empty. Caller owns returned instance.
  static Settings* Open(
      const std::string& config_file_path,
      const std::string& history_file_path);

  // Gets the value of a string setting, with default config as fallback.
  std::string GetString(const std::string& key);
  // Gets the value of an integer setting, with default config as fallback.
  int GetInt(const std::string& key);
  // Gets the value of an enum setting, with default config as fallback. Enum
  // options are specified as a STL map or unordered_map from string to value.
  template <
      typename V = int, typename MapT = std::unordered_map<std::string, V> >
  V GetEnum(const std::string& key, const MapT& enum_map);

  // Returns the default configuration.
  static const rapidjson::Document& GetDefaultConfig();

 private:
  // Path to config file.
  std::string _config_file_path;
  // Loaded config.
  rapidjson::Document _config;

  // Path to history file.
  std::string _history_file_path;
  // Loaded history file.
  rapidjson::Document _history;

  // Use factory method Open() to create and initialize an instance.
  Settings(){};
};

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                              Implementation                               *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

template <typename V, typename MapT>
V Settings::GetEnum(const std::string& key, const MapT& enum_map) {
  const std::string string_value = GetString(key);
  typename MapT::const_iterator it = enum_map.find(string_value);
  if (it != enum_map.end()) {
    return it->second;
  }
  const rapidjson::Document& default_config = GetDefaultConfig();
  if (default_config.HasMember(key.c_str()) &&
      default_config[key.c_str()].IsString()) {
    it = enum_map.find(default_config[key.c_str()].GetString());
    if (it != enum_map.end()) {
      return it->second;
    }
  }
  fprintf(stderr, "Unable to get enum config value \'%s\'\n", key.c_str());
  abort();
}

#endif

