#include "WeightModifier.h"
#include <iostream>
#include "Modifier.h"
#include "../util/FileReader.h"
using namespace std;

void WeightModifier::handleLine(FileReader *fileReader) {
    if (fileReader->key == "factor") {
        this->factor = stof(fileReader->value);
    } else if (fileReader->key == "modifier") {
        this->modifiers.push_back(Modifier(fileReader));
    } else {
        cout << "\33[31m" << "ERROR: Unhandled key \"" << fileReader->key << "\" in Modifier" << "\033[0m" << endl;
    }
}

WeightModifier::WeightModifier(FileReader *fileReader) {
    auto depth = fileReader->depth;

    while(fileReader->read_block(depth)) {
        this->handleLine(fileReader);
    }
}
