add_executable(dec_3 main.cpp)

add_library(dec_3_logic INTERFACE)

target_include_directories(dec_3_logic
                           INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/logic)

target_link_libraries(dec_3 PRIVATE dec_3_logic utils)
target_link_libraries(dec_3_logic INTERFACE utils)
