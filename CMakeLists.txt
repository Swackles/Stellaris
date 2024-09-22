cmake_minimum_required(VERSION 3.10.0)
project(StellarisEventsParser VERSION 0.0.1 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 17)

enable_testing()

add_subdirectory(src)

add_executable(StellarisEventsParser ./src/main.cpp)

target_link_libraries(StellarisEventsParser PRIVATE util)

set_property(TARGET StellarisEventsParser PROPERTY CXX_STANDARD 17)

#
# Catch2 test
#
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

get_filename_component(TEST_FILE_PATH ./test ABSOLUTE)
configure_file(./test/config.h.in ../test/config.h)

#
# src/section/research tests
#
add_library(
    sectionResearchTests
    test/section/research/ResearchCategory.cpp
    test/section/research/ResearchTier.cpp
)

target_include_directories(sectionResearchTests PUBLIC test/)

target_link_libraries(sectionResearchTests
    PRIVATE
    sectionResearch
        Catch2::Catch2
)

#
# src/shared tests
#
add_library(
    sharedTests
    test/shared/ScriptedVariables.cpp
)

target_include_directories(sharedTests PUBLIC test/)

target_link_libraries(sharedTests
    PRIVATE
    shared
        Catch2::Catch2
)

#
# src/util tests
#
add_library(
    utilTests
    test/util/FileReader.cpp
)

target_include_directories(utilTests PUBLIC test/)

target_link_libraries(utilTests
    PRIVATE
        util
        Catch2::Catch2
)

#
# all tests
#
add_executable(allTests test/test.cpp)

target_include_directories(allTests PUBLIC test/)

target_link_libraries(allTests
    PRIVATE
        sectionResearchTests
        sharedTests
        utilTests

        Catch2::Catch2WithMain
)

include(CTest)
include(Catch)
catch_discover_tests(allTests)