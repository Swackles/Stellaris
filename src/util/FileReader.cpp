#include <iostream>
#include <regex>
#include <string>
#include <fstream>
#include "FileReader.h"
using namespace std;

string COMMENT_CHARACTER = "#";

FileReader::FileReader(string fileName) {
    filePath = fileName;
    infile.open(fileName);
}

bool FileReader::ignore_line() {
    string clean_line = strip_string(line);

    return clean_line == "";
}

string FileReader::strip_string(string value) {
    return regex_replace(value, regex("^\\s+|(.*?)\\s+$"), "$1");
}

bool FileReader::read_block() {
    read_line();

    return key != StellarisKey::END_SECTION;
}

void FileReader::setKey(string keyString) {
    if (keyString == "}") {
        key = StellarisKey::END_SECTION;
    } else if (keyString == "planet_event") {
        key = StellarisKey::PLANET_EVENT;
    } else {
        cout << "\33[31m" << "ERROR: key \"" << keyString << "\" not found in \"" << filePath << ":" << fileLine << "\"" << "\033[0m" << endl;
    }
}

bool FileReader::read_line() {
    bool eof;

    // Resets the key and value
    key = StellarisKey::EMPTY;
    value = "";

    if (buffered_line == "") {
        eof = getline(infile, line).eof();
        fileLine += 1;
    } else {
        line = buffered_line;
        buffered_line = "";
        eof = false;
    }

    // Strip comment from line
    line = regex_replace(line, regex("(.*?)#.*$"), "$1");

    if (ignore_line()) {
        return read_line();
    } else {
        long seperator_pos = line.find("=");

        setKey(strip_string(line.substr(0, seperator_pos)));

        if (key != StellarisKey::END_SECTION) {
            value = strip_string(line.substr(seperator_pos + 1, line.length()));

            // Handle multiple lines on same line
            // ex: country_event = { id = paragon.550 scopes = { from = event_target:dead_leader_clone } }
            if (value.length() == 1) {
                return !eof;
            } else if (value.compare(0, 1, "{") == 0) {
                buffered_line = value.substr(1, line.length());
                value = strip_string(value.substr(0, 1));
            } else if (value.substr(value.length() - 1, 1) == "}") {
                buffered_line = value.substr(value.length() - 1, 1);
                value = strip_string(value.substr(0, value.length() - 1));
            }
        }
    }

    return !eof;
}
