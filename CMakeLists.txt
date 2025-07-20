cmake_minimum_required(VERSION 3.22)

project(StarlineTestTask)

option(BUILD_TESTS "build tests" ON)

set(SOURCE_DIR ./src)
set(UNIT_TESTS_DIR ./unittests)
set(TESTS_DIR ./tests)

# main app

add_subdirectory(${SOURCE_DIR})

add_executable(main ${SOURCE_DIR}/main.cpp)

target_link_libraries(main PRIVATE 
    TrackerLib
    TrackingLib 
    TrackerReaderLib 
    TrackerFileWriterLib
    ProcessTrackedDataLib
)

if(BUILD_TESTS)
    # unittests
    add_subdirectory(${UNIT_TESTS_DIR})
endif()