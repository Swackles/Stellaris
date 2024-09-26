#include <iostream>
#include "Modifier.h"
#include "../util/FileReader.h"
#include "LogicOperators.h"
using namespace std;

void Modifier::handleLine(FileReader *fileReader) {
    if (fileReader->key == "factor") {
        this->factor = stof(fileReader->value);
    } else if (LogicOperators::isValidLogicOperator(&fileReader->key)) {
        this->operations.push_back(LogicOperators(&fileReader->key, fileReader));
    } else {
        cout << "\33[31m" << "ERROR: Unhandled key \"" << fileReader->key << "\" in Modifier" << "\033[0m" << endl;
    }
}

Modifier::Modifier(FileReader *fileReader) {
    auto depth = fileReader->depth;

    while(fileReader->read_block(depth)) {
        this->handleLine(fileReader);
    }
}
