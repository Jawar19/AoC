#include <filesystem>

void solve_part_one(std::filesystem::path &filepath);
int solve_part_two(std::filesystem::path &filepath);
void solve_part_two_jank(std::filesystem::path &filepath);
int floor_quotient(int, int);
int16_t extract_command(std::string_view line);
uint8_t calculate_position(int16_t delta, uint8_t current_position);
