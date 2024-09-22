#include <catch2/catch_all.hpp>
#include "../src/section/research/ResearchTier.h"
#include "../src/util/FileReader.h"
#include "config.h"
#include <fstream>
using namespace std;

TEST_CASE("ResearchTier") {
    SECTION("Reads research item") {
        FileReader fileReader = FileReader(test::getSectionResearchFile("/ResearchItem.txt"));
        ResearchTier researchTier;

        while(fileReader.read_line()) {
            researchTier = ResearchTier(stoi(fileReader.key), &fileReader);
        };

        REQUIRE( researchTier.tier == 1 );
        REQUIRE( researchTier.previouslyUnlocked == 0 );
    }
    
    SECTION("Reads empty research item") {
        FileReader fileReader = FileReader(test::getSectionResearchFile("/ResearchItemEmpty.txt"));
        ResearchTier researchTier;

        while(fileReader.read_line()) {
            researchTier = ResearchTier(stoi(fileReader.key), &fileReader);
        };

        REQUIRE( researchTier.tier == 0 );
        REQUIRE( researchTier.previouslyUnlocked == 0 );
    }
}
