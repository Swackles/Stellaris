#ifndef FileReader_H
#define FileReader_H

#include <string>
#include <fstream>
using namespace std;

class FileReader {
    private:
        ifstream infile;
        
        string filePath = "";
        string buffered_line = "";

        bool ignore_line();
        bool strip_comment();
        string strip_string(string value); 
        void setKey(string keyString);
    
    public:
        int fileLine = 0;
        string line;
        string key;
        string value;
        bool endOfFileReached = false;

        // Each section start will increase it by one and every section decrease will reduce it
        unsigned short int depth = 0;
        FileReader(string file_name);

        bool read_line();
        bool read_block(unsigned short int startDepth);
};
#endif