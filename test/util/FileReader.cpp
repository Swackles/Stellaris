#include <catch2/catch_all.hpp>
#include "../src/util/FileReader.h"
#include "config.h"
#include <fstream>
using namespace std;

string getFile(string fileName) {
    string basePath = test::file_path;
    return basePath + "/util/resources/" + fileName;
}

TEST_CASE("FileReader::read_block") {
    SECTION("Reads basic until end") {
        FileReader fileReader = FileReader(getFile("/BasicFile.txt"));

        while(fileReader.read_block(0)) {
        };

        REQUIRE( fileReader.fileLine == 5 );
    }
    
    SECTION("Reads deep blocks and ignores the depth") {
        FileReader fileReader = FileReader(getFile("/DeepFile.txt"));

        int blocksReturned = 0;
        fileReader.read_line();
        auto startDepth = fileReader.depth;

        while(fileReader.read_block(startDepth)) {
            blocksReturned += 1;
        };

        REQUIRE( fileReader.fileLine == 12 );
        REQUIRE( blocksReturned == 2 );
    }
}

TEST_CASE("FileReader::read_line") {
    SECTION("Reads file until end") {
        string filePath = test::file_path;
        FileReader fileReader = FileReader(getFile("/BasicFile.txt"));

        while(fileReader.read_line()) {  };

        REQUIRE( fileReader.fileLine == 5 );
    }

    SECTION("Run over ignored lines") {
        string filePath = test::file_path;
        int linesReturned = 0;
        FileReader fileReader = FileReader(getFile("/IgnoredLines.txt"));

        string lineThreeText[6];
        while(fileReader.read_line()) {
            linesReturned += 1;
            lineThreeText[fileReader.fileLine] = fileReader.key + " - " + fileReader.value;
        };

        REQUIRE( linesReturned == 3 );
        REQUIRE( fileReader.fileLine == 6 );
        
        REQUIRE( lineThreeText[3] == "event - {" );
        REQUIRE( lineThreeText[4] == "test_key - test_value" );
        REQUIRE( lineThreeText[5] == "} - " );
    }
}