add_executable(dec_2 main.cpp)

add_library(dec_2_logic INTERFACE)

target_include_directories(dec_2_logic
                           INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/logic)

target_link_libraries(dec_2 PRIVATE dec_2_logic utils)
target_link_libraries(dec_2_logic INTERFACE utils)
