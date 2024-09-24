add_library(
    shared
    LogicOperators.h
    LogicOperators.cpp

    ScriptedVariables.h
    ScriptedVariables.cpp
)

target_include_directories(shared
    PRIVATE
        util
)