/* Util header only to get input files from AoC
 * Author: Jacob Warrer
 */

#ifndef GET_INPUT_H
#define GET_INPUT_H

#include "config.h"

#include <curl/curl.h>
#include <curl/easy.h>

#include <cstddef>
#include <cstdio>
#include <format>
#include <fstream>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <string>

using dl_status = struct {
    std::ostream *os;
    size_t dl_total;
};

inline static size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream) {
    auto *status = (dl_status *)stream;
    size_t written = size * nmemb;
    status->os->write(static_cast<const char *>(ptr), (long)written);

    if (status->os->fail()) {
        written = 0;
    }

    status->dl_total += written;
    return written;
}

inline static std::string get_session_key(const std::string &path) {
    ConfigMap config = parse_env_file(path);

    if (!config.contains("SESSION_KEY")) {
        std::cerr << "Session key not found in config" << "\n";
        throw std::runtime_error("Session key not found");
    }

    return config["SESSION_KEY"];
}

inline bool get_stuff(const char *url, const char *filename) {
    std::cout << "Getting stuff" << "\n";

    std::ofstream output_file(filename, std::ios::binary);

    if (!output_file.is_open()) {
        std::cerr << "Failed to open file: " << filename << "\n";
        return false;
    }

    dl_status status = {.os = &output_file, .dl_total = 0};
    CURL *curl_handle = curl_easy_init();

    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, &status);
    curl_easy_setopt(curl_handle, CURLOPT_URL, url);
    curl_easy_setopt(curl_handle, CURLOPT_VERBOSE, true);
    curl_easy_setopt(curl_handle, CURLOPT_NOPROGRESS, 1L);
    curl_easy_setopt(curl_handle, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curl_handle, CURLOPT_FAILONERROR, 1L);

    curl_easy_setopt(curl_handle, CURLOPT_COOKIESESSION, 1L);
    std::string cookie_str = std::format("session={};", get_session_key(".env"));

    curl_easy_setopt(curl_handle, CURLOPT_COOKIE, cookie_str.c_str());

    CURLcode result = curl_easy_perform(curl_handle);

    curl_easy_cleanup(curl_handle);

    if (result != CURLE_OK) {
        std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(result) << "\n";
        remove(filename);
        return false;
    }

    std::cout << "Successfully downloaded " << status.dl_total << " bytes to " << filename << "\n";
    return true;
}

#endif // !GET_INPUT_H
