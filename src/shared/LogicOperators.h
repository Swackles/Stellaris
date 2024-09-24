#pragma once
#include <list>
#include <string>
#include "../util/FileReader.h"
using namespace std;

class LogicOperators {
    public:
        // https://stellaris.paradoxwikis.com/Conditions
        string gate;
        list<string> operations;
        list<LogicOperators> childOperations;

        static bool isValidLogicOperator(string *key);
        LogicOperators(string *gate, FileReader *fileReader);
};
