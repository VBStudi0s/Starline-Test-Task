cmake_minimum_required(VERSION 3.22)
project(StarlineTestTaskUnittests)

# Setup testing
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIR})

# Add test cpp file
add_executable(runUnitTests
    test_tracker.cpp
)

# Link test executable against gtest & gtest_main
target_link_libraries(runUnitTests PRIVATE 
    ${GTEST_LIBRARY_DEBUG} ${GTEST_MAIN_LIBRARY_DEBUG}
    GTest::gtest_main
    TrackerLib
)

add_test(
    NAME runUnitTests
    COMMAND runUnitTests
)