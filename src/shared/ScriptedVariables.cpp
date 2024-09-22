#include <filesystem>
#include "ScriptedVariables.h"
#include "../util/FileReader.h"
using namespace std;

float ScriptedVariables::getValue(string *key) {
    return this->variables[*key];
}

ScriptedVariables::ScriptedVariables(string *stellarisPath) {
    string path = *stellarisPath + "/common/scripted_variables";

    for (const auto & entry : filesystem::directory_iterator(path)) {
        FileReader fileReader(entry.path().string());

        while(fileReader.read_line()) {
            this->variables.insert({ fileReader.key, stof(fileReader.value) });
        }
    }
}
