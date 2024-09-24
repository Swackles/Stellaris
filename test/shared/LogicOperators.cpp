#include <catch2/catch_all.hpp>
#include <iterator>
#include "../src/util/FileReader.h"
#include "../src/shared/LogicOperators.h"
#include "config.h"
#include <iostream>
using namespace std;

TEST_CASE("LogicOperators") {
    SECTION("Reads basic logic operator") {
        FileReader fileReader(test::getSharedFile("/LogicOperator.txt"));
        fileReader.read_line();

        LogicOperators logicOperators(&fileReader.key, &fileReader);

        REQUIRE( logicOperators.childOperations.empty() == true );

        REQUIRE( logicOperators.operations.empty() == false );
        REQUIRE( logicOperators.operations.size() == 3 );

        list<string>::iterator it = logicOperators.operations.begin();

        REQUIRE( *it == "has_technology = tech_mine_exotic_gases" );
        advance(it, 1);
        REQUIRE( *it == "has_technology = tech_exotic_gases" );
        advance(it, 1);
        REQUIRE( *it == "has_country_flag = has_market_access" );
    }

    SECTION("Reads deep basic logic operator") {
        FileReader fileReader(test::getSharedFile("/LogicOperatorDeep.txt"));
        fileReader.read_line();

        LogicOperators logicOperators(&fileReader.key, &fileReader);

        REQUIRE( logicOperators.childOperations.empty() == false );
        REQUIRE( logicOperators.childOperations.size() == 3 );

        list<LogicOperators>::iterator it = logicOperators.childOperations.begin();
        REQUIRE( it->gate == "NOT" );
        REQUIRE( it->childOperations.empty() == true );
        REQUIRE( it->operations.empty() == false );
        REQUIRE( it->operations.size() == 1 );
        REQUIRE( *it->operations.begin() == "has_technology = tech_mine_exotic_gases" );
        advance(it, 1);

        REQUIRE( it->gate == "NOT" );
        REQUIRE( it->childOperations.empty() == true );
        REQUIRE( it->operations.empty() == false );
        REQUIRE( it->operations.size() == 1 );
        REQUIRE( *it->operations.begin() == "has_technology = tech_exotic_gases" );
        advance(it, 1);

        REQUIRE( it->gate == "NOT" );
        REQUIRE( it->childOperations.empty() == true );
        REQUIRE( it->operations.empty() == false );
        REQUIRE( it->operations.size() == 1 );
        REQUIRE( *it->operations.begin() == "has_country_flag = has_market_access" );
        advance(it, 1);

        REQUIRE( logicOperators.operations.empty() == false );
        REQUIRE( logicOperators.operations.size() == 1 );
        REQUIRE( *logicOperators.operations.begin() == "has_country_flag = has_market_access" );
    }
}
