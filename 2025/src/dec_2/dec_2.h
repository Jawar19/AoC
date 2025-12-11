/**
 * Header for functions to solve AoC day 2
 */

#ifndef DEC_2_H
#define DEC_2_H

#include <algorithm>
#include <cctype>
#include <cstddef>
#include <filesystem>
#include <format>
#include <fstream>
#include <functional>
#include <iostream>
#include <print>
#include <ranges>
#include <span>
#include <spanstream>
#include <stdexcept>
#include <string>
#include <string_view>

class SolveDayTwo {
  public:
    SolveDayTwo(std::filesystem::path &path) {
        this->file = new std::ifstream(path.c_str());
        if (!this->file->is_open()) {
            std::string err_msg = std::format("Could not open file in path: %s", path.c_str());
            throw std::runtime_error(err_msg);
        }
    };
    ~SolveDayTwo() {

        if (this->file) {
            if (this->file->is_open()) {
                this->file->close();
            }
            delete file;
        }
    };

    std::ranges::iota_view<long, long> get_range_from_input() {
        std::string line{};
        if (this->file->is_open()) {
            std::getline(*this->file, line, ',');
        }
        std::string_view line_view(line);
        size_t eq_index = line_view.find('-');
        if (eq_index == std::string_view::npos) {
            return {};
        }

        long start{_parse_long(line_view.substr(0, eq_index))};
        long end{_parse_long(line_view.substr(eq_index + 1))};
        return std::views::iota(start, end + 1);
    }

    static bool filter_p1(long x) {
        const std::string input_str = std::to_string(x);
        std::string_view input_view = input_str;
        if (input_view.size() % 2 != 0) {
            return false;
        }
        size_t midpoint = input_view.size() / 2;
        auto first_half = input_view.substr(0, midpoint);
        auto second_half = input_view.substr(midpoint);
        for (size_t i = 0; i < midpoint; ++i) {
            if (first_half.at(i) != second_half.at(i)) {
                return false;
            };
        }

        return true;
    };

    static bool filter_p2(long x) {
        const std::string input_str = std::to_string(x);
        std::string_view input_view = input_str;
        std::size_t pattern_length = input_view.size() / 2;
        auto initial = input_view.substr(0, pattern_length);

        for (; pattern_length > 0; --pattern_length) {
            auto chunked_view = input_view | std::ranges::views::chunk(pattern_length);

            bool current_view_is_valid{false};

            auto first_chunk = chunked_view.front();
            auto chunked_view_drop = chunked_view | std::views::drop(1);
            for (auto chunk : chunked_view_drop) {
                if (!std::ranges::equal(first_chunk, chunk)) {
                    // std::println("not equal");
                    current_view_is_valid = false;
                    break;
                }
                current_view_is_valid = true;
            }

            if (current_view_is_valid) {
                return true;
            }
        };
        return false;
    };

    long solve_part_one() {
        long total = 0;
        while (!this->file->eof()) {
            auto range = get_range_from_input();

            auto filtered_range = range | std::views::filter(&SolveDayTwo::filter_p1);
            total += std::ranges::fold_left(filtered_range, 0L, std::plus<>());
        }
        return total;
    };

    long solve_part_two() {
        this->reset_file_ptr();
        long total = 0;
        size_t iteration{};
        while (!this->file->eof()) {
            auto range = get_range_from_input();

            auto filtered_range = range | std::views::filter(&SolveDayTwo::filter_p2);
            total += std::ranges::fold_left(filtered_range, 0L, std::plus<>());
        }
        return total;
    };

  private:
    std::ifstream *file = nullptr;

    void reset_file_ptr() {
        if (!this->file->is_open()) {
            throw std::runtime_error("file not open");
        }
        this->file->clear();
        this->file->seekg(0);
    };

    static long _parse_long(const std::string_view &s) {
        long result;
        std::span<const char> char_span(s.data(), s.size());
        std::ispanstream ss(s);
        ss >> result;
        if (ss.fail()) {
            throw std::invalid_argument("Input does not start with a valid long type");
        }

        if (ss.peek() != std::char_traits<char>::eof()) {
            char c;
            while (ss.get(c)) {
                if (!std::isspace(static_cast<unsigned char>(c))) {
                    throw std::invalid_argument("Input contains trailing now-whitespace chars");
                }
            }
        }
        return result;
    }
};

#endif // DEC_2_H
