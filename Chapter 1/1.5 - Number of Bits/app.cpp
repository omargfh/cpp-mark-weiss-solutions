#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int bitCount(int x)
{
    int maskEven, maskNibble, maskByte, maskBytes, maskDouble, exp;

    maskEven = (((0x55 << 8) + 0x55) << 16) + ((0x55 << 8) + 0x55);
    exp = (x & maskEven) + ((x >> 1) & maskEven);
    maskNibble = (((0x33 << 8) + 0x33) << 16) + ((0x33 << 8) + 0x33);
    exp = (exp & maskNibble) + ((exp >> 2) & maskNibble);
    maskByte = (((0x0F << 8) + 0x0F) << 16) + ((0x0F << 8) + 0x0F);
    exp = (exp & maskByte) + ((exp >> 4) & maskByte);
    exp = (exp & ((0xFF << 16) + 0xFF)) + ((exp >> 8) & ((0xFF << 16) + 0xFF));
    return (exp & ((0xFF << 8) + 0xFF)) + ((exp >> 16) & ((0xFF << 8) + 0xFF));
}

template<typename Object>
int bitwiseManipulation(Object x) {
    Object result = x & static_cast<Object>(0x1);
    size_t bits = sizeof(Object) * 8 - 1;
    while(bits != 0) {
        x >>= 1;
        result += (x & static_cast<Object>(0x1));
        bits--;
    }
    return static_cast<int>(result);
}
int recursive(int x) {
    if (x == 1)
        return 1;
    if (x == 0)
        return 0;
    return (x & 0x1) + recursive((x >> 1) & ~(0x1 << ((sizeof(int) * 8) - 1)));
}

int recursiveEfficient(unsigned int x) {
    if (x == 1)
        return 1;
    if (x == 0)
        return 0;
    return x % 2 ? recursive(x / 2) + 1 : recursive(x / 2);
}

int main() {
    int x = -2339;
    cout << bitCount(x) << endl;
    cout << bitwiseManipulation(x) << endl;
    cout << recursive(x) << endl;
    cout << recursiveEfficient(x) << endl;
    return 0;
}