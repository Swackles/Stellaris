#include <string>
#include <fstream>
#include "./StellarisKey.cpp"
using namespace std;

class FileReader {
    private:
        ifstream infile;
        
        string filePath = "";
        int fileLine = 0;
        string buffered_line = "";

        bool ignore_line();
        bool strip_comment();
        string strip_string(string value); 
        void setKey(string keyString);
    
    public:
        string line;
        StellarisKey key;
        string value;

        FileReader(string fileName);

        bool read_line();
        bool read_block();
};