#include "dec_1.h"

#include "config.h"

#include <cassert>
#include <cmath>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <string_view>

#define PART_TWO_ANSWER 6379

void solve_part_one(std::filesystem::path &filepath) {
    // define relevant variables and starting conditions
    uint16_t password = 0;
    uint8_t current_position = 50;

    // load the input file
    std::ifstream input_file(filepath);
    if (!input_file.is_open()) {
        throw std::runtime_error(std::format("Could not open file {}", filepath.string()));
        return;
    }

    // Parse file with format yxx, where y is direction and xx is number of steps
    std::string line;
    while (std::getline(input_file, line)) {
        int16_t delta = extract_command(line);
        current_position = calculate_position(delta, current_position);
        // std::cout << "delta: " << std::setw(6) << delta
        //           << "\tnew position: " << static_cast<int>(current_position) << '\n';
        if (current_position == 0) {
            ++password;
        };
    }
    std::cout << "Password for puzzle 1 is: " << password << '\n';
}

void solve_part_two_jank(std::filesystem::path &filepath) {
    int password = 0;
    int position = 50;

    // load the input file
    std::ifstream input_file(filepath);
    if (!input_file.is_open()) {
        throw std::runtime_error(std::format("Could not open file {}", filepath.string()));
        return;
    }
    std::string line;
    while (std::getline(input_file, line)) {
        int clicks = extract_command(line);

        for (int i = 0; i < std::abs(clicks); ++i) {

            if (clicks < 0) {
                position = (position - 1) % 100;
            } else {
                position = (position + 1) % 100;
            }

            if (position == 0) {
                ++password;
            }
        }
    }
    std::cout << "Password for Puzzle 2 jank is " << password << '\n';
}

int solve_part_two(std::filesystem::path &filepath) {
    // define relevant variables and starting conditions
    uint16_t password = 0;
    uint16_t current_position = 50;

    // load the input file
    std::ifstream input_file(filepath);
    if (!input_file.is_open()) {
        throw std::runtime_error(std::format("Could not open file {}", filepath.string()));
        return -1;
    }
    std::string line;
    while (std::getline(input_file, line)) {
        std::cout << line << '\t';
        int delta = extract_command(line);
        int new_position = (int)calculate_position((short)delta, current_position);
        int mod = 99 + 1;

        int raw = current_position + delta;

        int full_turns = raw / mod;
        int clicks = raw % mod;

        int crossings = std::abs(full_turns);

        std::cout << full_turns << '\t' << current_position << '\t' << (delta) << '\t'
                  << new_position << '\t' << clicks << '\t' << crossings << '\n';

        password += crossings;
        current_position = new_position;
    }
    return password;
}

int16_t extract_command(std::string_view line) {
    std::string_view line_view = trim(line);
    std::string_view direction_view = trim(line_view.substr(0, 1));
    std::string_view number_view = trim(line_view.substr(1));

    int16_t delta = std::stoi(std::string(number_view));

    if (std::string(direction_view) == "L") {
        delta *= -1;
    }

    return delta;
}

uint8_t calculate_position(int16_t delta, const uint8_t current_position) {
    const int maxval = 99;
    const int minval = 0;
    const int mod = maxval + 1 - minval;

    int raw_position = current_position + delta;

    int position = (raw_position % mod + mod) % mod;

    return position;
}
