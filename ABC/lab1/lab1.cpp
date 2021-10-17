#include <iostream>
#include <string>
#include <math.h>
#include <vector>

using namespace std;


int sum5x5(int lhs, int rhs) {
    int promise = 0, res = 0, tens = 0;
    for (int tmp = lhs + rhs; tmp > 0; tmp/=10, tens++) {
        int dig = tmp % 10 + promise;
        promise = dig / 5;
        dig %= 5;
        res += dig * pow(10, tens);
    }
    res += promise * pow(10, tens);
    return res;
}

int mult5x5(int lhs, int rhs) {
    int res = 0, tens = 0;
    vector<long> sums;
    for (int tmp = rhs; tmp > 0; tmp /= 10, tens++) {
        int dig = tmp % 10;
        int nw = 0;
        for (int i = 0; i < dig; i++)
            nw = sum5x5(nw, lhs);
        sums.push_back(nw * pow(10, tens));
    }

    for (auto el : sums) {
        res = sum5x5(res, el);
    }
    return res;
}

pair<int, bool> conv7_5(int given) {
    pair <int, bool> res;
    res.second = false;
    int tens = 0;
    for (int tmp = given; tmp > 0; tmp /= 10, tens++) {
        int num = tmp % 10;
        if (num > 6 && num < 0) {
            res.second = true;
            return res;
        }

    }
}

int main()
{
    cout << mult5x5(1234, 1234);
    cout << "Введите число в семиричной системе: ";
    string str;
    cin >> str;
}