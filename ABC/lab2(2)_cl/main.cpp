#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <fstream>
#include <iomanip>
#include <exception>
#include <algorithm>

using namespace std;

string& eraser(string& str, char ch){
    str.erase(str.find(ch), 1);
    return str;
}

int getIndexOf16ric(char a){
    if (a >= 'A' && a <= 'F'){
        return 10+int(a - 'A');
    }
    else if (a >= '0' && a <= '9'){
        return int(a - '0');
    }
    else throw "Недопустимый символ '" + to_string(a) + "'";
}

char getNumberOf16ric(int num){
    if (num > 9 && num < 16)
        return char('A' + num%10);
    else if (num >= 0 && num <= 9)
        return char('0' + num);
    else
        throw "Недопустимый индекс " + to_string(num);
}

string conv_from_10(double given, int newbase, int prec = -1) {
    string res;
    int int_part = int(given);
    double rel_part = given - int_part;
    if (prec < 0)
        prec = int(to_string(rel_part).length());
    for (int tmp = int_part; tmp > 0; tmp /= newbase) {
        int num = tmp % newbase;
        char c = getNumberOf16ric(num);
        res = c + res;
    }
    res += '.';
    for (int i = 0; i < prec; i++){
        rel_part *= newbase;
        int num = int(rel_part);
        rel_part -= num;
        char c = getNumberOf16ric(num);
        res += c;
    }
    return res;
}

pair<char, char> summator(char lhs, char rhs){
    pair<char, char> ret;
    int a = getIndexOf16ric(lhs);
    int b = getIndexOf16ric(rhs);
    int sum = a + b;
    ret.second = getNumberOf16ric(sum%16);
    ret.first = getNumberOf16ric(sum/16);
    return ret;
}

pair<char, char> multiplier(char lhs, char rhs){
    pair<char, char> ret;
    int lhs10 = getIndexOf16ric(lhs);
    int rhs10 = getIndexOf16ric(rhs);
    int res = lhs10 * rhs10;
    ret.second = getNumberOf16ric(res%16);
    ret.first = getNumberOf16ric(res/16);
    return ret;
}

string sum(const string& lhs, const string& rhs){
    string ret, tmp1, tmp2;

    tmp1 = lhs;
    int real_part1 = tmp1.find('.') != -1? int(tmp1.substr(tmp1.find('.')+1).length()) : 0;

    tmp2 = rhs;
    int real_part2 = tmp1.find('.') != -1? int(tmp2.substr(tmp2.find('.')+1).length()) : 0;

    int dif = abs(real_part2 - real_part1);
    string concat;
    for (int i = 0; i < dif; i++){
        concat += "0";
    }
    if (real_part1 > real_part2){
        tmp2 += concat;
    } else {
        tmp1 += concat;
    }

    string lhs_rev = tmp1;
    reverse(lhs_rev.begin(), lhs_rev.end());

    string rhs_rev = tmp2;
    reverse(rhs_rev.begin(), rhs_rev.end());

    int i = 0;
    char promise = '0';
    bool finlft = false, finrgt = false;
    while (true){
        char left, right;
        string res = " ";
        if (finlft || i > lhs_rev.length()-1){
            left = '0';
            finlft = true;
        } else {
            left = lhs_rev[i];
        }
        if (finrgt || i > rhs_rev.length()-1){
            right = '0';
            finrgt = true;
        } else {
            right = rhs_rev[i];
        }
        if (finlft && finrgt && promise == '0')
            break;

        if (left == '.' && right == '.') {
            res[0] = '.';
        } else {
            auto[tprom1, tres] = summator(left, right);
            auto[tprom2, ttres] = summator(tres, promise);
            promise = summator(tprom1, tprom2).second;
            res[0] = ttres;
        }
        ret += res;
        i++;
    }

    reverse(ret.begin(), ret.end());

    return ret;
}

string mult(const string& lhs, const string& rhs) {
    string tmp1, tmp2;
    tmp1 = lhs;
    int real_part1 = int(tmp1.substr(tmp1.find('.')+1).length());

    tmp2 = rhs;
    int real_part2 = int(tmp2.substr(tmp2.find('.')+1).length());

    int dif = abs(real_part2 - real_part1);
    string concat;
    for (int i = 0; i < dif; i++){
        concat += "0";
    }
    if (real_part1 > real_part2){
        tmp2 += concat;
    } else {
        tmp1 += concat;
    }

    vector<string> sums;

    int k = 0;
    for (int i = int(tmp2.length()-1); i >= 0; i--){
        string tmpsum = "0.0";
        for (int j = 0; tmp2[i] != '.' && j < getIndexOf16ric(tmp2[i]); j++){
            tmpsum = sum(tmpsum, tmp1);
        }
        for (int j = 0; j < k; j++){
            tmpsum += "0";
        }
        sums.push_back(eraser(tmpsum, '.'));
        k++;
    }

    string tmpsum = "0";
    for (auto str : sums){
        tmpsum = sum(tmpsum, str);
    }
    int len = int(tmpsum.length());
    int rpart = real_part1 + real_part2;
    tmpsum += tmpsum[len-1];
    for (int i = len-1; i >= len - rpart; i--)
        tmpsum[i] = tmpsum[i-1];
    tmpsum[len-rpart-1] = '.';
    return tmpsum.substr(0, tmpsum.find('.') + 1 + max(real_part1, real_part2));
}

double conv_to_10(const string& str, int base) {
    int powr = int(str.find('.')) - 1;
    double res = 0.0;
    for (char i : str){
        if (i == '.')
            continue;
        res += getIndexOf16ric(i) * pow(base, powr);
        powr--;
    }
    return res;
}

pair<vector<double>, vector<string>> calculate(const string& inp){
    pair<vector<double>, vector<string>> ret;
    string fnum16, snum16, rnum16;
    stringstream str_inp(inp);
    double fnum10, snum10, rnum10;
    str_inp >> fnum10 >> snum10;
    fnum16 = conv_from_10(fnum10, 16);
    snum16 = conv_from_10(snum10, 16);
    rnum16 = mult(fnum16, snum16);
    rnum10 = conv_to_10(rnum16, 16);
    ret.first.push_back(fnum10);
    ret.first.push_back(snum10);
    ret.first.push_back(rnum10);
    ret.second.push_back(fnum16);
    ret.second.push_back(snum16);
    ret.second.push_back(rnum16);
    return ret;
}

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");
    string num;
    while (getline(in, num)) {
        try {
            auto[ns10, ns16] = calculate(num);
            out << ns10[0] << " -> " << ns16[0] << endl << ns10[1] << " -> " << ns16[1] << endl;
            out << "Результат: " << ns16[2] << " -> " << ns10[2] << endl;
        }
        catch (string& ex) {
            out << "Ошибка! " << ex << endl;
        }
    }
    out.close();
}

