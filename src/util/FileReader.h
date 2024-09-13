#include <string>
#include <fstream>
using namespace std;

class FileReader {
    private:
        ifstream infile;

        string buffered_line = "";

        bool ignore_line();
        bool strip_comment();
        string strip_string(string value); 

    public:
        string line;
        string key;
        string value;

        FileReader(string fileName);

        bool read_line();
};