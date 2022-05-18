#include <iostream>
#include <vector>
#include <cmath>
#include <tuple>
#include <algorithm>
#include "matrix.h"
using namespace std;

class WordPuzzle {
    public:
        WordPuzzle(int rows, int cols, vector<char> & characters, vector<string> & wordList):rows(rows), cols(cols){
            grid.resize(rows, cols);
            load(characters);
            loadWordList(wordList);
        }
        WordPuzzle(int rows, int cols, vector<char> & characters):rows(rows), cols(cols){
            grid.resize(rows, cols);
            load(characters);
        }
        WordPuzzle(int rows, int cols) {
            grid.resize(rows, cols);
        }
        WordPuzzle() { }

        void load(vector<char> & characters) {
            if (characters.size() == rows * cols) {
                for(int i = 0; i < rows; i++) {
                    for (int j = 0; j < cols; j++) {
                        grid[i][j] = characters[i * rows + j];
                    }
                }
            }
        }

        void loadWordList(vector<string> & wordList) {
            words = wordList;
        }

        void print() const {
            for(int i = 0; i < rows; i++) {
                if (i == 0) {
                    cout << "  ";
                    for (int j = 0; j < cols; j++) {
                        cout << j + 1<< " ";
                    }
                    cout << endl;
                }
                for (int j = 0; j < cols; j++) {
                    if (j == 0) {
                        cout << i + 1 << " ";
                    }
                    cout << grid[i][j] << " ";
                }
                cout << endl;
            }
        }

        void solve() {
            for(int i = 0; i < rows; i++) {
                check_row(i, POSITIVE);
                check_row(i, NEGATIVE);
            }
            for(int j = 0; j < cols; j++) {
                check_column(j, POSITIVE);
                check_column(j, NEGATIVE);
            }
            for(int k = 0; k < rows + cols; k++) {
                check_diagonal(k, POSITIVE);
                check_diagonal(k, NEGATIVE);
                check_flipped_diagonal(k, POSITIVE);
                check_flipped_diagonal(k, NEGATIVE);
            }
            for (const tuple<string, tuple<int, int>> & x : results) {
                cout << "Word Found: " << get<0>(x);
                cout << " at (i = " << get<0>(get<1>(x)) << ", j = " << get<1>(get<1>(x)) << ")" << endl;
            }
            if (words.size() == 0)
                cout << "Game Completed!" << endl;
            else {
                cout << "Missing Words: ";
                for (string & x : words)
                    cout << x << " ";
                cout << endl;
            }
        }


    private:

        enum direction {
            POSITIVE,
            NEGATIVE
        };

        Matrix<char> grid{0, 0};
        vector<string> words;
        int rows;
        int cols;
        vector<tuple<string, tuple<int, int>>> results;

        void check_routine(vector<char> & v, int i, int j, int k, int direction) {
            std::string s(v.begin() + j, v.begin() + k);
            if (direction == NEGATIVE) {
                reverse(s.begin(), s.end());
            }

            auto found = std::find(words.begin(), words.end(), s);
            if (found != words.end()) {
                tuple<string, tuple<int, int>> t = make_tuple(s, make_tuple(i, j));
                results.push_back(t);
                words.erase(found);
            }
        }

        void check_row(int i, int direction) {
            for (int j = 0; j < cols; j++) {
                for (int k = j; k < cols + 1; k++) {
                    check_routine(grid[i], i, j, k, direction);
                }
            }
        }

        void check_column(int j, int direction) {
            vector<char> rotated(rows);
            for (int i = 0; i < rows; i++) {
                rotated[i] = grid[i][j];
            }
            for (int i = 0; i < rotated.size(); i++) {
                for (int k = i; k < rotated.size() + 1; k++) {
                    check_routine(rotated, j, i, k, direction);
                }
            }
        }

        void check_diagonal(int k, int direction) { /* diagonal index from 1 to (rows + cols) */
            vector<char> v(0);
            if (k <= (rows + cols)) {
                for(int i = 0; i < rows; i++) {
                    for (int j = 0; j < cols; j++) {
                        if (i + j + 2 == k) {
                            v.push_back(grid[i][j]);
                        }
                    }
                }
            }
            for (int j = 0; j < v.size(); j++) {
                for (int k = j; k < v.size() + 1; k++) {
                    check_routine(v, -1, j, k, direction);
                }
            }
        }

        void check_flipped_diagonal(int k, int direction) { /* diagonal index from 1 to (rows + cols) */
            direction = !direction; /* result of flip */
            Matrix<char> flippedGrid(rows, cols);
            for (int i = 0; i < rows; i++) {
                flippedGrid[i] = grid[rows - 1 - i];
            }
            vector<char> v(0);
            if (k <= (rows + cols)) {
                for(int i = 0; i < rows; i++) {
                    for (int j = 0; j < cols; j++) {
                        if (i + j + 2 == k) {
                            v.push_back(flippedGrid[i][j]);
                        }
                    }
                }
            }
            for (int j = 0; j < v.size(); j++) {
                for (int k = j; k < v.size() + 1; k++) {
                    check_routine(v, -1, j, k, direction);
                }
            }
        }
};

int main() {

    vector<char>  v{'t','h','i','s',
                    'w','a','t','s',
                    'o','a','h','g',
                    'f','g','d','t'};
    vector<std::string> s{"this", "two", "fat", "that"};
    WordPuzzle puzzle(4, 4, v, s);
    puzzle.print();
    puzzle.solve();
    return 0;
}