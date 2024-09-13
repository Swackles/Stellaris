#include <iostream>
#include "util/FileReader.h"
using namespace std;

int main()
{
    FileReader file_reader("");

    while (file_reader.read_line()) {
        cout << "\"" + file_reader.key + "\" + \"" + file_reader.value + "\"" << endl;
    }

    return 0;
}
