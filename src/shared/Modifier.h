#pragma once
#include <list>
#include <string>
#include "../util/FileReader.h"
#include "LogicOperators.h"
using namespace std;

class Modifier {
    private:
        void handleLine(FileReader *fileReader);

    public:
        float factor;
        list<LogicOperators> operations;

        Modifier(FileReader *fileReader);
};
