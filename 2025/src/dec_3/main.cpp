/*
 * Advent of code 2025 december 2nd
 * Author: Jacob Warrer
 */
#include "dec_3.h"
#include "get_input.h"

#include <cassert>
#include <chrono>
#include <cstdint>
#include <filesystem>
#include <iostream>
#include <print>
#include <sstream>
#include <stdexcept>

const static uint8_t DAY{'3'};
// const static char *TYPE{"test"};
const static char *TYPE{"input"};

auto main(int argc, char *argv[]) -> int {
    std::cout << "Hello Advent of code" << '\n';

    std::stringstream path{};
    std::stringstream url{};

    path << "input/dec_" << DAY << "/" << TYPE << ".txt";
    url << "https://adventofcode.com/2025/day/" << DAY << "/input";

    auto filename = std::filesystem::relative(path.str());
    std::filesystem::create_directories(filename.parent_path());

    if (!std::filesystem::exists(filename)) {
        bool succes = get_stuff(url.str().c_str(), filename.c_str());
    } else {
        std::cout << "Input file found in " << filename.parent_path() << ", skipping download !"
                  << "\n";
    }
    try {
        SolveDayThree solver(filename);
        auto start_time = std::chrono::system_clock::now();
        long p1_result = solver.solve_part_one();
        std::chrono::duration<double> duration = std::chrono::system_clock::now() - start_time;

        start_time = std::chrono::system_clock::now();
        long p2_result = solver.solve_part_two();
        std::chrono::duration<double> duration_2 = std::chrono::system_clock::now() - start_time;

        std::println("Solution to part 1 is {}, finished in {} s", p1_result, duration.count());
        std::println("Solution to part 2 is {}, finished in {} s", p2_result, duration_2.count());

    } catch (std::runtime_error e) {
        std::cerr << "caught runtime error " << e.what() << '\n';
        return 1;
    }

    return 0;
}
