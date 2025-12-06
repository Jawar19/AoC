add_library(utils INTERFACE)

target_compile_features(utils INTERFACE cxx_std_23)
target_link_libraries(utils INTERFACE curl)
target_link_libraries(utils INTERFACE stdc++fs)

target_include_directories(
  utils INTERFACE ${CMAKE_CURRENT_SOURCE_DIR} # Exposes the utils/ folder
)
