cmake_minimum_required(VERSION 3.10)


# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  runTests
    test_update.cpp
    test_Object_code_check.cpp
  )

target_link_libraries(
  runTests PUBLIC libpower GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(runTests)