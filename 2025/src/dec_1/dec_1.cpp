#include "dec_1.h"

#include "config.h"

#include <cassert>
#include <cmath>
#include <cstdint>
#include <cstdlib>
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
    uint16_t dial = 50;

    // load the input file
    std::ifstream input_file(filepath);
    if (!input_file.is_open()) {
        throw std::runtime_error(std::format("Could not open file {}", filepath.string()));
        return -1;
    }

    std::string line;
    int mod = 99 + 1;
    int crossings;
    while (std::getline(input_file, line)) {

        int delta = extract_command(line);
        int new_position = (int)calculate_position((short)delta, dial);
        int next = dial + delta;

        crossings = std::abs(floor_quotient(next, mod) - floor_quotient(dial, mod));
        // Check for a left turn crossing the 0 boundary, where cycle math gives 0
        if (delta < 0 && dial > 0 && new_position != 0 && next < 0 && crossings == 0) {
            crossings = 1;
        }

        if (crossings == 0) {
            bool crossed_zero = (delta < 0) && (dial > 0) && (next <= 0);
            // Note: If dial is 50, delta is -50, next is 0. This is true.

            bool crossed_hundred = (delta > 0) && (dial < mod) && (next >= mod);

            if (crossed_zero || crossed_hundred) {
                crossings = 1;
            }
        }
        if (dial == 0 && crossings > 0) {
            if (crossings > 0) {
                --crossings;
            }
        }
        password += crossings;
        dial = new_position;

        std::cout << line << '\t' << dial << '\t' << delta << '\t' << crossings << '\n';
    }
    std::cout << "--------" << '\n';
    std::cout << "|" << std::setw(6) << password << "|" << '\n';
    std::cout << "--------" << '\n';
    return password;
}

int floor_quotient(int a, int mod) {
    int q = a / mod;
    int r = a % mod;

    if (r < 0) {
        --q;
    }
    return q;
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
