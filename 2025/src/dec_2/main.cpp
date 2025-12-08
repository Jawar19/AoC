/*
 * Advent of code 2025 december 2nd
 * Author: Jacob Warrer
 */
// #include "dec_2.h"
#include "get_input.h"

#include <cassert>
#include <filesystem>
#include <iostream>
#include <stdexcept>

auto main(int argc, char *argv[]) -> int {
    std::cout << "Hello Advent of code" << '\n';

    // auto filename = std::filesystem::relative("input/dec_2/test.txt");
    auto filename = std::filesystem::relative("input/dec_2/input.txt");
    std::filesystem::create_directories(filename.parent_path());

    if (!std::filesystem::exists(filename)) {
        bool succes = get_stuff("https://adventofcode.com/2025/day/2/input", filename.c_str());
    } else {
        std::cout << "Input file found in " << filename.parent_path() << ", skipping download!"
                  << "\n";
    }
    try {
        // solve_part_one(filename);
        // solve_part_two(filename);
    } catch (std::runtime_error e) {
        std::cerr << "caught runtime error " << e.what() << '\n';
        return 1;
    }

    return 0;
}
