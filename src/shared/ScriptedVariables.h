#pragma once
#include <map>
#include <string>
using namespace std;

class ScriptedVariables {
    private:
        map<string, float> variables;

    public:
        float getValue(string *key);
        ScriptedVariables(string *stellarisPath);
};
