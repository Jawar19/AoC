/*
 * Config read util file, creates config map from provided path
 */

#ifndef CONFIG_H
#define CONFIG_H

#include <algorithm> // For std::remove_if
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>
#include <unordered_map>
#include <utility>

using ConfigMap = std::unordered_map<std::string, std::string>;

inline std::string_view trim(std::string_view s) {
    const char *white_space_str = " \t\n\r";
    size_t start = s.find_first_not_of(white_space_str);
    if (std::string_view::npos == start) {
        return "";
    }
    size_t end = s.find_last_not_of(white_space_str);
    return s.substr(start, end - start + 1);
}

inline ConfigMap parse_env_file(const std::string &filename) {

    ConfigMap config;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Could not open provided configuration file " << filename << "\n";
        return config;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::string_view line_view = trim(line);

        if (line_view.empty() || line_view.starts_with('#')) {
            continue;
        }

        size_t eq_index = line_view.find('=');
        if (eq_index == std::string_view::npos) {
            continue;
        }

        std::string_view key_view = line_view.substr(0, eq_index);
        std::string_view value_view = line_view.substr(eq_index + 1);

        std::string key(trim(key_view));
        std::string value(trim(value_view));

        if (!key.empty()) {
            config[std::move(key)] = std::move(value);
        }
    }

    return config;
}

#endif // CONFIG_H
