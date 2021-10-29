#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <cmath>
#include <exception>

using namespace std;

int notL(int l, int r = 0){
    return l==0 ? 1 : 0;
}

int xorL(int l, int r){
    return l xor r;
}

int orL(int l, int r){
    return l or r;
}

int andL(int l, int r){
    return l and r;
}

int impL(int l, int r){
    return orL(notL(l), r);
}

int shfL(int l, int r){
    return notL(andL(l, r));
}

int eqvL(int l, int r){
    return l == r;
}

int getPriority (int (*lgt)(int l, int r)){
    if (lgt == notL)
        return 1;
    if (lgt == andL)
        return 2;
    if (lgt == orL || lgt == xorL)
        return 3;
    if (lgt == impL)
        return 4;
    if (lgt == eqvL)
        return 5;
    return 6;
}

bool lftPriority(int (*lgt)(int l, int r), int (*rgt)(int l, int r)){
    return getPriority(lgt) <= getPriority(rgt);
}

struct formula{
    formula* lhs = nullptr;
    formula* rhs = nullptr;
    int (*fncPtr)(int l, int r) = nullptr;
    int* res = nullptr;
};

int countFormula(formula* f){
    if (f->res == nullptr)
        return (*f->fncPtr)(countFormula(f->lhs), countFormula(f->rhs));
    return *(f->res);
}

void strip(string& from, char what){
    auto c = from.find(what);
    while (c == 0){
        from = from.substr(1);
        c = from.find(what);
    }
    while (c == from.length()-1) {
        from = from.erase(from.length() - 1);
        c = from.find(what);
    }
}

formula* getFormula(string& str){
    static map<char, int*> perem;
    auto res = new formula;
    strip(str, ' ');
    if (str.length() == 1){
        if (perem.find(str[0]) == perem.end()){
            int* a = new int;
            perem[str[0]] = a;
        }
        res->res = perem[str[0]];
    } else {
        if (str[0] == 'n'){
            res->fncPtr = notL;
            strip(str, 'n');
            if (str[0] != '(' || str[str.length()-1] != ')')
                throw "not found \"n(...)\" expression when tried to work with 'not' statement";
        }
    }
    return res;
}

auto getTable(const string& str) {
    vector<vector<char>> res(int(pow(2.0, 4.0)), vector<char>(5));



    return res;
}

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");
    string formula;
    while (getline(in, formula)) {
        try {
            auto res = getTable(formula);
            for (const auto& str : res){
                for (auto el : str){
                    out << el <<'|';
                }
                out << endl;
            }
        }
        catch (const char* ex) {
            out << "Ошибка! " << ex << endl;
        }
    }
    out.close();
}
