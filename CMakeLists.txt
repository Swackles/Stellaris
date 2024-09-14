cmake_minimum_required(VERSION 3.5.0)
project(StellarisEventsParser VERSION 0.0.1 LANGUAGES C CXX)

include(CTest)
enable_testing()

add_subdirectory(src)

add_executable(StellarisEventsParser ./src/main.cpp)

target_link_libraries(StellarisEventsParser PRIVATE util)

set_property(TARGET StellarisEventsParser PROPERTY CXX_STANDARD 17)
