#include <iostream>
#include <vector>
#include <cstdio>
#include <regex>
#include <fstream>
#include <sstream>

using namespace std;

void include(string filename, vector<string> included) {
    remove("a.parsed"); /* create new file */

    int total_includes = 0; /* check for termination, when no more includes remain */
    /* open files */
    ifstream in;
    in.open(filename);

    ofstream out;
    out.open("a.parsed", ios::app);

    string line;
    while (getline(in, line)){
        regex regex("#include \"([\\w\\-_. ]+)\"");
        std::smatch m;
        auto match = std::regex_match(line, m, regex);
        if (match) {
            ifstream includefile;
            includefile.open(m[1].str());
            if(!includefile.is_open()) {
                cout << "Cannot find " << m[1].str() << " in directory." << endl;
                remove("a.parsed");
                exit(1);
            }
            string subline;
            if (included.size() == 0 || !(find(included.begin(), included.end(), subline) != included.end())) {
                included.push_back(m[1].str());
                while (getline(includefile, subline)){
                    out << subline << endl;
                }
                total_includes++;
            }
            else {
                cout << included.size() << endl;
                cout << included[0] << endl;
                cout << "Cyclic import error." << endl;
                remove("a.parsed");
                exit(1);
            }
        }
        else {
            out << line << endl;
        }
    }
    if (total_includes != 0) {
        remove("old.parsed");
        rename("a.parsed", "old.parsed");
        include("old.parsed", included);
    }
    else {
        remove("old.parsed");
    }
}

int main() {
    string filename = "samplefile.cpp";
    vector<string> included{};
    include(filename, included);
}