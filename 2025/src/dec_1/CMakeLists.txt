add_library(dec_1_logic STATIC dec_1.cpp)

target_include_directories(dec_1_logic PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(dec_1 main.cpp)
target_link_libraries(dec_1 PRIVATE dec_1_logic utils)
target_link_libraries(dec_1_logic PRIVATE utils)
