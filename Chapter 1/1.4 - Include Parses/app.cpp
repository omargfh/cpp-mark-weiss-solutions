#include <iostream>
#include <vector>
#include <regex>
#include <fstream>
#include <sstream>

using namespace std;

/* outputs to a.out */
void include(string filename) {
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
        }
        else {
            out << line << endl;
        }
    }
}

int main() {
    string filename = "samplefile.cpp";
    include(filename);
}