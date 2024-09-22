#pragma once
#include "../../util/FileReader.h"
using namespace std;

class ResearchCategory {
    public:
        string name;
        string imagePath;

        ResearchCategory(string name, FileReader* fileReader);
};
