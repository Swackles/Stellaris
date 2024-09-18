cmake_minimum_required(VERSION 3.5.0)
project(StellarisEventsParser VERSION 0.0.1 LANGUAGES C CXX)

include(CTest)
enable_testing()

add_subdirectory(src)

add_executable(StellarisEventsParser ./src/main.cpp)

target_link_libraries(StellarisEventsParser PRIVATE util)

set_property(TARGET StellarisEventsParser PROPERTY CXX_STANDARD 17)

# Catch2 test
Include(FetchContent)

add_library(Catch INTERFACE)
target_include_directories(Catch
    INTERFACE
        test/
)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.4.0
)

FetchContent_MakeAvailable(Catch2)

# Copy assets for FileReader tests
set (test_assets
    test/util/assets/BasicFile.txt
)

get_filename_component(TEST_FILE_PATH ./test/util/resources ABSOLUTE)
configure_file(./test/util/config.h.in ../test/util/config.h)

add_executable(unit_tests
    test/util/FileReader.cpp
)

target_include_directories(unit_tests PUBLIC test/)

target_link_libraries(unit_tests
    PRIVATE
        util
        Catch2::Catch2WithMain
)
