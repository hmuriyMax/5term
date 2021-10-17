#include <iostream>
#include <map>
#include <vector>

using namespace std;

void RouteFinder(map<int, int>& res, const map<int, vector<int>>& ruins, int cities, int length, int spawn = 1, int already = 0){
    if (length!=0) {
        for (int i = 1; i < cities; i++) {
            if (i != spawn && !ruins.at(spawn).at(i)) {
                if (i == 1)
                    res[already + 1] += 1;
                else
                    RouteFinder(res, ruins, cities, length - 1, i, already + 1);
            }
        }
    }

}

int main()
{

}