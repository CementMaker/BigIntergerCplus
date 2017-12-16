#include "big_integer.h"
#include "utilities.h"
#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
#include <vector>
#include <unistd.h>

using namespace std;

//three '-'
big_integer operator-(const big_integer &num1, const big_integer &num2) {

    std::string a = num1.big_number;
    std::string b = num2.big_number;

    char num1_sign, num2_sign, ans_sign = '+';
    num1_sign = get_num_sign(a);
    num2_sign = get_num_sign(b);

    if (num1_sign == '-' && num2_sign == '+') {
        big_integer _num2, _num1 = big_integer(a.substr(1, a.size() - 1));
        if (b[0] == '+') _num2 = big_integer(b.substr(1, b.size() - 1));
        else _num2 = num2;
        return big_integer("-" + (_num1 + _num2).big_number);
    } else if (num1_sign == '+' && num2_sign == '-') {
        big_integer _num1, _num2 = big_integer(b.substr(1, b.size() - 1));
        if (a[0] == '+') _num1 = big_integer(a.substr(1, a.size() - 1));
        else _num1 = num1;
        return _num1 + _num2;
    } else if (num1_sign == '-' && num2_sign == '-'){
        big_integer _num1 = big_integer (a.substr (1, a.size() - 1));
        big_integer _num2 = big_integer (b.substr (1, b.size() - 1));
        return _num2 - _num1;
    } else {
        if (a[0] == '+') {
            big_integer _num1 = big_integer (a.substr (1, a.size() - 1));
            if (b[0] == '+') {
                big_integer _num2 = big_integer(b.substr(1, b.size() - 1));
                return _num1 - _num2;
            } else {
                return _num1 - num2; 
            }
        } else {
            if (b[0] == '+') {
                big_integer _num2 = big_integer (b.substr (1, b.size() - 1));
                return num1 - _num2;
            }
        }
    }

    a = del_pre_zero(a);
    b = del_pre_zero(b);

    bool _flag = 0;
    if (num1 == num2) return big_integer("0");
    if (num1 < num2) {
        string tmp = a;
        a = b;
        b = tmp;
        _flag = 1;
    }
    std::string::size_type len1 = a.size();
    std::string::size_type len2 = b.size();
    std::string::size_type i, j, index;

    for (i = len1, j = len2; i > 0 && j > 0; --i, --j) {
        if (a[i - 1] >= b[j - 1]) {
            a[i - 1] = a[i - 1] - b[j - 1] + '0';
        } else {
            int flag = 1;
            a[i - 1] = a[i - 1] - b[j - 1] + 10 + '0';
            for (index = i - 1; index > 0 && flag; --index) {
                int tmp = (a[index - 1] - '1' + 10) % 10;
                if (a[index - 1] == '0') {
                    a[index - 1] = tmp + '0';
                } else {
                    a[index - 1] = tmp + '0';
                    flag = 0;
                }
            }
        }
    }
    for (index = 0; index < a.size(); ++index) {
        if (a[index] != '0')
            break;
    }
    if (index == a.size()) index--;
    a = a.substr(index, a.size() - index);
    if (_flag) return '-' + a;
    return a;
}

big_integer operator-(const long long &num1, const big_integer &num2) {
    char p[10000]; sprintf (p, "%lld", num1);
    string tmp(p);
    return big_integer(tmp) - num2;
}

big_integer operator-(const big_integer &num1, const long long &num2) {
    char p[10000]; sprintf (p, "%lld", num2);
    string tmp(p);
    return num1 - big_integer(tmp);
}