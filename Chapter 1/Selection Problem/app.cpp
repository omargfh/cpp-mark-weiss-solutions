#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>
using namespace std;
using namespace std::chrono;

class SArray {
    public:
        SArray(int size = 0) : data(size){}
        void read(vector<int> & rhs) {
            if (data.size() <= rhs.size()) {
                for (int i = 0; i < data.size(); i++) {
                    data[i] = rhs[i];
                }
            }
            sort(data.begin(), data.end(), greater<int>());
        }
        void append(int & rhs) {
            if (rhs > data[data.size() - 1]) {
                for (int i = 0; i < data.size(); i++) {
                    if (rhs > data[i]) {
                        const int tmp = static_cast<const int &&>(data[i]);
                        data[i] = static_cast<const int &&>(rhs);
                        for (int j = data.size() - 1; j > (i + 1); j--) {
                            std::swap(data[j], data[j-1]);
                        }
                        data[i+1] = tmp;
                        break;
                    }
                }
            }
        }
        int report() { return data[data.size() - 1]; }
        int report(int i) { return data[i]; }
        void r() {
            for(const int & x : data)
                cout << x << endl;
        }
    private:
        vector<int> data;
};

void median(vector<int> & v) {

    int n = floor(v.size() / 2) + 1;
    SArray obj(n);
    obj.read(v);
    for(int i = n; i < v.size(); i++) {
        obj.append(v[i]);
    }
    if (v.size() % 2) { /* if odd */
        cout << "median is: " << obj.report() << endl;
    }
    else {
        cout << "median is: " << (obj.report() + obj.report(n - 2)) / 2 << endl;
    }
}

int testRandomArray(int size) {
    vector<int> arr(size);
    for (int i = 0; i < arr.size(); i++) {
        arr[i] = rand() % 10000;
    }
    auto start = steady_clock::now();
    median(arr);
    auto stop = steady_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);
    cout << arr.size() << ", " << duration.count() << endl;
    return duration.count();
}

void bubbleSort(vector<int> v) {
    int i, j;
    for (i = 0; i < v.size() - 1; i++)
        for (j = 0; j < v.size() - i - 1; j++)
            if (v[j] > v[j + 1])
                std::swap(v[j], v[j + 1]);
}

int testClassicMethod(int size) {

    vector<int> arr(size);
    for (int i = 0; i < arr.size(); i++) {
        arr[i] = rand() % 10000;
    }
    auto start = steady_clock::now();
    bubbleSort(arr);

    if (arr.size() % 2) { /* if odd */
        cout << "median is: " << arr[floor(arr.size() / 2) + 1] << endl;
    }
    else {
        cout << "median is: " << (arr[floor(arr.size() / 2) + 1] + arr[floor(arr.size() / 2)]) / 2 << endl;
    }

    auto stop = steady_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << arr.size() << ", " << duration.count() << endl;
    return duration.count();
}

int main() {


    cout << "Half Sort Method" << endl;
    testRandomArray(1);
    testRandomArray(2);
    testRandomArray(4);
    testRandomArray(8);
    testRandomArray(16);
    testRandomArray(32);
    testRandomArray(64);
    testRandomArray(128);
    testRandomArray(256);
    testRandomArray(512);
    testRandomArray(1024);
    testRandomArray(2048);
    testRandomArray(4096);
    testRandomArray(8192);
    testRandomArray(16384);
    testRandomArray(33668);

    cout << "Classic Method" << endl;
    testClassicMethod(1);
    testClassicMethod(2);
    testClassicMethod(4);
    testClassicMethod(8);
    testClassicMethod(16);
    testClassicMethod(32);
    testClassicMethod(64);
    testClassicMethod(128);
    testClassicMethod(256);
    testClassicMethod(512);
    testClassicMethod(1024);
    testClassicMethod(2048);
    testClassicMethod(4096);
    testClassicMethod(8192);
    testClassicMethod(16384);
    testClassicMethod(33668);

    return 0;
}