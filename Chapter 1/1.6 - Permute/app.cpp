#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

void permute( const string & str, int low, int high ) {

    string s = str;
    if (low == high) {
        cout << str << endl;
    }

    for(int i = low; i <= high; i++) {
        swap(s[low], s[i]);
        permute(s, low + 1, high);
        swap(s[low], s[i]);
    }
}

void permute( string & str ) {
    permute(str, 0, str.size() - 1);
}

int main() {
    string sample = "abc";
    permute(sample);
}