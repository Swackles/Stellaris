#include <catch2/catch_all.hpp>
#include "../src/section/research/ResearchCategory.h"
#include "../src/util/FileReader.h"
#include "config.h"
#include <fstream>
using namespace std;

TEST_CASE("ResearchCategory") {
    SECTION("Reads research category") {
        FileReader fileReader = FileReader(test::getSectionResearchFile("/ResearchCategory.txt"));
        ResearchCategory researchCategory("material", &fileReader);

        REQUIRE( researchCategory.name == "material" );
        REQUIRE( researchCategory.imagePath == "gfx/interface/icons/technologies/categories/category_materials.dds" );
    }
}
