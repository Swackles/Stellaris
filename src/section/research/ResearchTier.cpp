#include "./ResearchTier.h"
#include <iostream>
using namespace std;

void ResearchTier::handleLine(FileReader* fileReader) {
    if (fileReader->key == "previously_unlocked") {
        previouslyUnlocked = stoi(fileReader->value);
    } else if (fileReader->key == "weight_modifier") {
        // Not needed
    } else {
        cout << "\33[31m" << "ERROR: Unhandled key \"" << fileReader->key << "\" in ResearchTier" << "\033[0m" << endl;
    }
}

ResearchTier::ResearchTier() { }

ResearchTier::ResearchTier(unsigned int tier, FileReader* fileReader) {
    this->tier = tier;
    int depth = fileReader->depth;

    while(fileReader->read_block(depth)) {
        this->handleLine(fileReader);
    };
}