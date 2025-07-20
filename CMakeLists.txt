cmake_minimum_required(VERSION 3.22)

project(StarlineTestTask)

set(SOURCE_DIR ./src)
set(UNIT_TESTS_DIR ./unittests)
set(TESTS_DIR ./tests)

add_subdirectory(${SOURCE_DIR})

add_executable(main ${SOURCE_DIR}/main.cpp)

# target_ling_libraries()