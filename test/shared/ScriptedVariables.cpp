#include <catch2/catch_all.hpp>
#include "../src/shared/ScriptedVariables.h"
#include "config.h"
using namespace std;

TEST_CASE("ScriptedVariables") {
    SECTION("Reads scripted variables") {
        string path = test::getStellarisPath();
        ScriptedVariables scriptedVariables(&path);

        string keyOne = "@scripted00";
        string keyTwo = "@scripted01";

        REQUIRE( scriptedVariables.getValue(&keyOne) == 1.0f );
        REQUIRE( scriptedVariables.getValue(&keyTwo) == 1.1f );
    }
}
