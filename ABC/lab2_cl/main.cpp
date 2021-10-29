#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <fstream>
#include <iomanip>
#include <exception>

using namespace std;

bool IsIn(char what, string where){
    return where.find('*') != -1;
}

int sum(int lhs, int rhs, int base) {
    int promise = 0, res = 0, tens = 0;
    int xnum = max(lhs, rhs);
    int nnum = min(lhs, rhs);
    for (; xnum > 0; xnum/=10, nnum/=10, tens++) {
        int dg1 = xnum%10;
        int dg2 = nnum%10;
        int num = dg1 + dg2 + promise;
        res += num % base * int(pow(10, tens));
        promise = num/base;
    }
    res += promise * int(pow(10, tens));
    return res;
}

int mult(int lhs, int rhs, int base) {
    int res = 0, tens = 0;
    vector<int> sums;
    for (int tmp = rhs; tmp > 0; tmp /= 10, tens++) {
        int dig = tmp % 10;
        int nw = 0;
        for (int i = 0; i < dig; i++)
            nw = sum(nw, lhs, base);
        sums.push_back(nw * int(pow(10, tens)));
    }

    for (auto el : sums) {
        res = sum(res, el, base);
    }
    return res;
}

int pow(int num, int pw, int base){
    int res = 1;
    for (int i=0; i<pw; i++){
        res = mult(num, res, base);
    }
    return res;
}

string conv_from_10(double given, int newbase, int prec) {
    string res = "";
    int int_part = int(given);
    double rel_part = given - int_part;
    for (int tmp = int_part; tmp > 0; tmp /= newbase) {
        int num = tmp % newbase;
        char c;
        if (num > 9)
            c = 'A' + num%10;
        else
            c = char(num) + char('0');
        res = c + res;
    }
    res += '.';
    for (int i = 0; i < prec; i++){
        rel_part *= newbase;
        int num = int(rel_part);
        char c;
        if (num > 9)
            c = 'A' + num%10;
        else
            c = char(num) + char('0');
        res += c;
    }
    return res;
}

string conv_to_10(int given, int newbase) {
    string res = "";
    for (int tmp = given; tmp > 0; tmp /= newbase) {
        int num = tmp % newbase;
        char c;
        if (num > 9)
            c = 'A' + num%10;
        else
            c = char(num) + char('0');
        res = c + res;
    }
    return res;
}

int count_precision(double real_part, int oldbase, int newbase){
    double tmp = 1.0;
    real_part *= 10;
    while (int(real_part) % 10 != 0){
        real_part *= 10;
        tmp /= oldbase;
    }
    int res = 0;
    while (tmp - 1/pow(newbase, res) < 0){
        res++;
    }
    return res;
}

pair<int, int> str_parser(const string& str){
    pair<int, int> res;
    string num_buf="";
    const string nums = "0123456789";
    bool is_reading_num = false, minus_flag = false;
    int num_counter = 0;
    for (char ch : str){
        if (IsIn(ch, str)){
            num_buf += ch;
            is_reading_num = true;
        }
        else if (is_reading_num){
            num_counter++;
            int tmp = stoi(num_buf);
            if (minus_flag){
                tmp *= -1;
            }
            switch (num_counter) {
                case 1:
                    res.first = tmp;
                    break;
                case 2:
                    res.second = tmp;
                    break;
                default:
                    throw "Лишние числа в строке!";
            }
        }
        else if (ch != ' ' && ch != '*' && ch!='-')
            throw "Лишние символы в строке!";
        else if (ch == '-' && !minus_flag)
            minus_flag = true;
        else if (minus_flag)
            throw "Неверная запись отрицательного числа";
    }
}

pair <vector<int>, vector<string>> new_num(string& num){
    pair <vector<int>, vector<string>> ret;
    bool less0 = false;
    try {
        string tmp = num;
        auto [first_num, second_num] = str_parser(num);
        string frs_16 = conv_from_10(first_num, 16)
        if (int_num<0)
            less0 = true;
        if (num != tmp) {
            string tmp2 = num;
            tmp2 = tmp2.substr(tmp2.find('.')+1);
            rel_num = stoi(tmp2) / pow(10, tmp2.length());
        }
        else
            rel_num = 0;
    }
    catch (const exception &ex) {
        ret.second = true;
        return ret;
    }
    int prec = count_precision(rel_num, 7, 5);
    auto[rnum_int, err] = conv_int(int_num, 7, 5);
    auto[rnum_rel, err2] = conv_real(rel_num, prec, 7, 5);
    if (!err && !err2) {
        ret.first.first = rnum_int + rnum_rel;
        ret.first.second = prec;
    } else {
        ret.second = true;
        return ret;
    }
    if (less0)
        ret.first.first*=-1;
    return ret;
}

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");
    string num;
    while (getline(in, num)) {
        try {
            auto[ns10, ns16] = new_num(num);
            out << ns10[0] << " -> " << ns16[0] << endl << ns10[1] << " -> " << ns16[1] << endl;
            out << "Результат: " << ns16[2] << " -> " << ns10[2] << endl;
        }
        catch (const char* ex) {
            out << "Ошибка! " << ex << endl;
        }
    }
    out.close();
}