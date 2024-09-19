#include <cstddef>
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

bool FileReader::read_block(unsigned short int startDepth) {
    bool eof = false;

    if (depth == startDepth) {
        read_line();

        return key != "}";
    } else {
        unsigned int startLine = fileLine + 1;

        while(depth > startDepth) {
            bool eof = read_line();

            if (!eof) return false;
        }
        read_line();

        if (startLine != fileLine) {
            cout << "\33[31m" << "Skipped lines in file: " << filePath << ":" << startLine << "-" << fileLine - 1 << "\033[0m" << endl;
        }
        return startDepth < depth || key != "}";
    }
}

unsigned int count(string str, const char sub[2]) {
    int count = 0;

    for (int i = 0; i < str.size(); i++) {
        if (str[i] == *sub) count++;
    }

    return count;
}

bool FileReader::read_line() {
    bool eof;

    key = "";
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
        if (eof) return !eof;
        
        return read_line();
    } else {
        size_t seperator_pos = line.find("=");

        key = strip_string(line.substr(0, seperator_pos));
        value = strip_string(line.substr(seperator_pos + 1, line.length()));

        if (key.find("}") != string::npos) {
            if (count(key, "}") > 1) {
                buffered_line = value.substr(1, value.length());
                key = "}";
            }

            value = "";
            depth = depth - 1;
        } else {
            // Handle multiple lines on same line
            // ex: country_event = { id = paragon.550 scopes = { from = event_target:dead_leader_clone } }
            if (value.length() == 1) {
            } else if (value.compare(0, 1, "{") == 0) {
                buffered_line = value.substr(1, line.length());
                value = strip_string(value.substr(0, 1));
            } else if (value.substr(value.length() - 1, 1) == "}") {
                auto posOfBlockEnd = value.find_first_of("}");

                buffered_line = value.substr(posOfBlockEnd, value.length());
                value = strip_string(value.substr(0, posOfBlockEnd));
            }

            if (value == "{") depth = depth + 1;
        }
    }

    return !eof;
}
