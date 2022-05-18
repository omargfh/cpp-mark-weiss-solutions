#include <iostream>
#include <vector>
#include <cstdio>
#include <regex>
#include <fstream>
#include <sstream>

using namespace std;

/* no gaurds on chain includes */
void include(string filename) {
    int total_includes = 0;
    /* open files */
    ifstream in;
    in.open(filename);

    ofstream out;
    out.open("a.parsed", ios::app);

    string line;
    while (getline(in, line)){
        regex regex("#include \"([\\w\\-. ]+)\"");
        std::smatch m;
        auto match = std::regex_match(line, m, regex);
        if (match) {
            ifstream includefile;
            includefile.open(m[1].str());
            string subline;
            while (getline(includefile, subline)){
                out << subline << endl;
            }
            total_includes++;
        }
        else {
            out << line << endl;
        }
    }
    if (total_includes != 0) {
        remove("old.parsed");
        rename("a.parsed", "old.parsed");
        include("old.parsed");
    }
    else {
        remove("old.parsed");
    }
}

int main() {
    string filename = "samplefile.cpp";
    include(filename);
}