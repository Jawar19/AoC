#include "solve_bc.h"

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <print>
#include <stdexcept>
#include <string>

class SolveDayThree : SolveBaseClass {

  public:
    explicit SolveDayThree(const std::filesystem::path &path) : SolveBaseClass(path) {};

    long solve_part_one() override {
        std::println("solve part one called");
        long total{0};
        std::println("{}", total);
        while (!input().eof()) {
            std::string bank = get_bettery_bank();
            if (bank.empty()) {
                continue;
            }
            int max{0};

            for (int i = 0; i < bank.length(); ++i) {
                for (int j = i + 1; j < bank.length(); ++j) {
                    char c1{bank[i]};
                    char c2{bank[j]};
                    int first_digit = c1 - '0';
                    int second_digit = c2 - '0';
                    int new_value = (first_digit * 10) + second_digit;
                    max = std::max(new_value, max);
                }
            }

            total += max;
        }
        return total;
    };

    long solve_part_two() override {
        long total{0};
        reset_file_ptr();
        while (!input().eof()) {
            std::string bank = get_bettery_bank();
            if (bank.empty()) {
                continue;
            }
            auto seq = max_subseq(bank, 12);
            total += std::stol(seq);
        }
        return total;
    };

    std::string get_bettery_bank() {
        if (!this->input() and this->input().is_open()) {
            throw std::runtime_error("Input file not open");
        }
        std::string line{};
        std::getline(input(), line);

        return line;
    };

  private:
    static std::string max_subseq(const std::string &s, std::size_t k) {
        std::size_t n = s.size();
        if (k >= n) {
            return s;
        }
        std::string st;
        st.reserve(k);
        std::size_t to_remove = n - k;
        for (size_t i = 0; i < n; ++i) {
            char c = s[i];
            while (!st.empty() && to_remove > 0 && st.back() < c) {
                st.pop_back();
                --to_remove;
            }
            st.push_back(c);
        }
        if (st.size() > k) {
            st.resize(k);
        }
        return st;
    };
};
