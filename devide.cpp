#include "big_integer.h"
#include "utilities.h"
#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
#include <vector>
#include <unistd.h>

using namespace std;

//three '/'
big_integer operator/(const big_integer &num1, const big_integer &num2) {
    std::string a = num1.big_number;
    std::string b = num2.big_number;

    char num1_sign, num2_sign, ans_sign = '+';
    num1_sign = get_num_sign(a);
    num2_sign = get_num_sign(b);

    big_integer _num1, _num2;
    if (num1_sign == '-' && num2_sign == '-') {
        _num1 = big_integer (a.substr (1, a.size() - 1));
        _num2 = big_integer (b.substr (1, b.size() - 1));
        return _num1 / _num2;
    } else if (num1_sign == '-' && num2_sign == '+') {
        _num1 = big_integer (a.substr (1, a.size() - 1));
        if (b[0] == '+') _num2 = big_integer (b.substr (1, b.size() - 1));
        else _num2 = num2;
        return big_integer('-' + (_num1 / _num2).big_number);
    } else if (num1_sign == '+' && num2_sign == '-') {
        _num2 = big_integer (b.substr (1, b.size() - 1));
        if (a[0] == '+') _num1 = big_integer (a.substr (1, a.size() - 1));
        else _num1 = num1;
        return big_integer('-' + (_num1 / _num2).big_number);
    } else {
        if (a[0] == '+') {
            _num1 = big_integer (a.substr (1, a.size() - 1));
            if (b[0] == '+') {
                _num2 = big_integer (b.substr (1, b.size() - 1));
            } else {
                _num2 = num2;
            }
            return _num1 / _num2;
        } else {
            _num1 = num1;
            if (b[0] == '+') {
                _num2 = big_integer (b.substr (1, b.size() - 1));
                return _num1 / _num2;
            }
        }
    }

    a = del_pre_zero(a);
    b = del_pre_zero(b);

    if (a == "0" || b == "0") {
        printf("RUNTIME ERROR\n");
        return big_integer ("0");
    }

    big_integer ans("0"), answer("0");
    big_integer a_copy(a), b_copy(b);
    while (a_copy >= b_copy) {
        ans = 0;
        while (a_copy >= b_copy) {
            if (ans == 0) {
                ans = 1;
            } else {
                ans = ans + ans;
            }
            if (b_copy + b_copy > a_copy) break;
            b_copy = b_copy + b_copy;
        }
        a_copy = a_copy - b_copy;
        answer = answer + ans;
        b_copy = b;
    }
    return answer;
}

big_integer operator/(const big_integer &num1, const long long &num2) {
    char p[10000]; sprintf(p, "%lld", num2);
    string tmp(p);
    return num1 / big_integer(tmp);
}

big_integer operator/(const long long &num1, const big_integer &num2) {
    char p[10000];
    sprintf(p, "%lld", num1);
    return num2 * (big_integer(string(p)));
}