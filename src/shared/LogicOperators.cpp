#include <iostream>
#include "LogicOperators.h"
#include "../util/FileReader.h"
using namespace std;

bool LogicOperators::isValidLogicOperator(string *key) {
    return *key == "AND" ||
           *key == "OR" ||
           *key == "NOT" ||
           *key == "NOR" ||
           *key == "NAND";
}

LogicOperators::LogicOperators(string *gate, FileReader *fileReader) {
    this->gate = *gate;
    auto depth = fileReader->depth;

    while(fileReader->read_block(depth)) {
        if (isValidLogicOperator(&fileReader->key)) {
            this->childOperations.push_back(LogicOperators(&fileReader->key, fileReader));
        } else {
            this->operations.push_back(fileReader->key + " = " + fileReader->value);
        }
    }
}
