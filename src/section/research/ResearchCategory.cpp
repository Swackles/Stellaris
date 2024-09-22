#include "./ResearchCategory.h"
#include <iostream>
using namespace std;

ResearchCategory::ResearchCategory(string name, FileReader* fileReader) {
    this->name = name;
    int depth = fileReader->depth;

    while(fileReader->read_block(depth)) {
        if (fileReader->key == "icon") {
            this->imagePath = fileReader->value;
        } else {
            cout << "\33[31m" << "ERROR: Unhandled key \"" << fileReader->key << "\" in ResearchCategory" << "\033[0m" << endl;
        }
    };
}