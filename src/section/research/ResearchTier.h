#include "../../util/FileReader.h"
using namespace std;

class ResearchTier {
    private:
        void handleLine(FileReader* fileReader);        

    public:
        unsigned int tier;
        unsigned int previouslyUnlocked = 0;

        ResearchTier();
        ResearchTier(unsigned int tier, FileReader* fileReader);
};