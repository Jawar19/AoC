include(FetchContent)

FetchContent_Declare(
  curl_repo
  GIT_REPOSITORY https://github.com/curl/curl.git
  GIT_TAG curl-8_17_0
  GIT_SHALLOW True)
FetchContent_MakeAvailable(curl_repo)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest/
  GIT_TAG v1.17.0)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt
    ON
    CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
