#include "big_integer.h"
#include "utilities.h"
#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
#include <vector>
#include <unistd.h>

using namespace std;

// three '+'
big_integer operator+(const big_integer &num1, const big_integer &num2) {

    std::string a = num1.big_number;
    std::string b = num2.big_number;

    char num1_sign, num2_sign, ans_sign = '+';
    num1_sign = get_num_sign(a);
    num2_sign = get_num_sign(b);


    if (num1_sign == '-' && num2_sign == '+') {
        big_integer _num2, _num1 = big_integer(a.substr(1, a.size() - 1));
        if (b[0] == '+') _num2 = big_integer(b.substr(1, b.size() - 1));
        else _num2 = num2;
        return _num2 - _num1;
    } else if (num1_sign == '+' && num2_sign == '-') {
        big_integer _num1, _num2 = big_integer(b.substr(1, b.size() - 1));
        if (a[0] == '+') _num1 = big_integer(a.substr(1, a.size() - 1));
        else _num1 = num1;
        return _num1 - _num2;
    } else if (num1_sign == '-' && num2_sign == '-'){
        big_integer _num1 = big_integer (a.substr (1, a.size() - 1));
        big_integer _num2 = big_integer (b.substr (1, b.size() - 1));
        return big_integer('-' + (_num2 + _num1).big_number);
    } else {
        big_integer _num1, _num2;
        if (a[0] == '+') {
            _num1 = big_integer (a.substr (1, a.size() - 1));
            if (b[0] == '+') _num2 = big_integer(b.substr(1, b.size() - 1));
            else _num2 = num2;
            return _num2 + _num1;
        } else {
            _num1 = num1;
            if (b[0] == '+') {
                _num2 = big_integer(b.substr(1, b.size() - 1));
                return _num1 + _num2;
            }
        }
    }

    a = del_pre_zero(a);
    b = del_pre_zero(b);

    if (a.size() < b.size()) {
        string tmp = a;
        a = b;
        b = tmp;
    }

    int len1 = a.size();
    int len2 = b.size();
    int flag = 0, flag_high = 0;

    for (int i = len1 - 1, j = len2 - 1; i >= 0 && j >= 0; --i, --j) {
        int  tmp = a[i] - '0' + b[j] - '0';
        a[i] = (tmp % 10 + '0');
        flag = tmp >= 10 ? 1 : 0;
        for (int index = i - 1; index >= 0 && flag; --index) {
            tmp = a[index] + 1 - '0';
            a[index] = (tmp % 10 + '0');
            flag = tmp >= 10 ? 1 : 0;
        }
        if (flag) {
            flag_high = 1;
        }
    }
    if (flag_high) {
        if (ans_sign == '+') a = "1" + a;
        else {
            a = "1" + a;
            a = '-' + a;
        }
    } else {
        if (ans_sign == '-') a = '-' + a;
    }
    big_integer c(a);
    return c;
}

big_integer operator+(const long long &num1, const big_integer &num2) {
    char p[10000]; sprintf (p, "%lld", num1);
    string tmp(p);
    return big_integer(tmp) + num2;
}

big_integer operator+(const big_integer &num1, const long long &num2) {
    char p[10000]; sprintf (p, "%lld", num2);
    string  tmp(p);
    return big_integer(tmp) + num1;
}
