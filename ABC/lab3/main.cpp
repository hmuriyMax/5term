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

struct formula{
    formula* lhs = nullptr;
    formula* rhs = nullptr;
    int (*fncPtr)(int l, int r) = nullptr;
    int* res = nullptr;
};

int countFormula(formula* f){
    if (f == nullptr)
        return 0;
    if (f->res == nullptr)
        return (*f->fncPtr)(countFormula(f->lhs), countFormula(f->rhs));
    return *(f->res);
}

void strip(string& from, char what){
    while (from[0] == what){
        from = from.substr(1);
    }
    while (from[from.length()-1] == what) {
        from = from.erase(from.length() - 1);
    }
}

bool CheckBr(const string& str){
    int brcount = 0;
    for (auto el : str){
        if (el == '(')
            brcount++;
        if (el == ')')
            brcount--;
        if (brcount < 0)
            return false;
    }
    if (brcount != 0)
        return false;
    return true;
}

void multiStrip(string& str) {
    strip(str, ' ');
    if (str[0] == '('){
        string tmp = str;
        tmp = tmp.substr(1, tmp.length()-2);
        if (CheckBr(tmp)) {
            str = str.substr(1);
            if (str[str.length() - 1] != ')')
                throw "')' not found!";
            str.erase(str.length() - 1);
        }
    }
}

bool TakesAll(string &str) {
    string tmp = str;
    tmp = tmp.substr(2, tmp.length()-3);
    return CheckBr(tmp);
}

formula* getFormula(string& str, map<char, int*>& perem){
    auto res = new formula;
    strip(str, ' ');
    if (str.length() == 1) {
        if (perem.find(str[0]) == perem.end()) {
            int *a = new int(0);
            perem[str[0]] = a;
        }
        res->res = perem[str[0]];
        return res;
    }
    if (str[0] == 'n' && TakesAll(str)){
        res->fncPtr = notL;
        strip(str, 'n');
        if (str[0] != '(' || str[str.length()-1] != ')')
            throw "not found \"n(...)\" expression when tried to work with 'not' statement";
        string tmp = str.substr(1, str.length()-2);
        res->lhs = getFormula(tmp, perem);
        return res;
    }
    vector<int (*)(int, int)> funcs;
    vector<int> position;
    int brcount = 0;
    int i;
    for (i = 0; i < str.length(); i++) {
        char ch = str[i];
        if (ch == ')') {
            if (brcount == 1) {
            }
            if (brcount < 1)
                throw "wrong symbol found: ')'";
            brcount--;
        }
        if (ch == '(') {
            brcount++;
            continue;
        }
        if (brcount == 0)
            switch (ch) {
                case '+':
                    funcs.push_back(xorL);
                    position.push_back(i);
                    break;
                case 'V':
                    funcs.push_back(orL);
                    position.push_back(i);
                    break;
                case '&':
                    funcs.push_back(andL);
                    position.push_back(i);
                    break;
                case '>':
                    funcs.push_back(impL);
                    position.push_back(i);
                    break;
                case '/':
                    funcs.push_back(shfL);
                    position.push_back(i);
                    break;
                case '=':
                    funcs.push_back(eqvL);
                    position.push_back(i);
                    break;
                default:
                    continue;
            }
    }
    for (i = 7; i > 0; i--){
        int j = 0;
        int k = 0;
        bool found = false;
        for (auto el : funcs){
            if (getPriority(el) == i) {
                found = true;
                k = j;
            }
            j++;
        }
        if (found){
            i = k;
            break;
        }
    }
    if (funcs.size() == 0)
        throw "operators not found!";
    res->fncPtr = funcs[i];
    string str1 = str;
    str1.erase(position[i]);
    string str2 = str.substr(position[i] + 1);
    multiStrip(str1);
    multiStrip(str2);
    res->lhs = getFormula(str1, perem);
    res->rhs = getFormula(str2, perem);
    return res;
}

void sumMap(int& num, map<char, int*>& perem){
    num++;
    int tmp = num;
    auto el = prev(perem.end());
    while (el != prev(perem.begin())){
        *el->second = tmp % 2;
        tmp/=2;
        el = prev(el);
    }
}

void printTable(ostream& out, string& str) {
    map<char, int*> perem;
    out << "Formula: " << str << endl;
    auto f = getFormula(str, perem);
    unsigned int num = perem.size();
    for (auto el : perem){
        out << el.first <<" | ";
    }
    out << "res" << endl;
    int n = 0;
    for (int i = 0; i < pow(2, num); i++, sumMap(n, perem)){
        for (auto el : perem){
            out << *el.second <<" | ";
        }
        out << countFormula(f) << endl;
    }
    out << endl;
}

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");
    string formula;
    while (getline(in, formula)) {
        try {
            printTable(out, formula);
        }
        catch (const char* ex) {
            out << "Ошибка! " << ex << endl << endl;
        }
    }
    out.close();
}