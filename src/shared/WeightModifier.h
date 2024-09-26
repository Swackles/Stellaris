#pragma once
#include <list>
#include <string>
#include "../util/FileReader.h"
#include "Modifier.h"
using namespace std;

class WeightModifier {
    private:
        void handleLine(FileReader *fileReader);

    public:
        float factor = 0;
        list<Modifier> modifiers;

        static bool isValidLogicOperator(string* key);
        WeightModifier(FileReader* fileReader);
};
