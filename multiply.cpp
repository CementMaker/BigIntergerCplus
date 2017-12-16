#include "big_integer.h"
#include "utilities.h"
#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
#include <vector>
#include <unistd.h>

using namespace std;

// three '*'
big_integer operator*(const big_integer &num1, const big_integer &num2) {
    std::string a = num1.big_number;
    std::string b = num2.big_number;

    char num1_sign, num2_sign, ans_sign = '+';
    num1_sign = get_num_sign(a);
    num2_sign = get_num_sign(b);

    big_integer _num1, _num2;
    if (num1_sign == '-' && num2_sign == '-') {
        _num1 = big_integer (a.substr (1, a.size() - 1));
        _num2 = big_integer (b.substr (1, b.size() - 1));
        return _num1 * _num2;
    } else if (num1_sign == '-' && num2_sign == '+') {
        _num1 = big_integer (a.substr (1, a.size() - 1));
        if (b[0] == '+') _num2 = big_integer (b.substr (1, b.size() - 1));
        else _num2 = num2;
        return big_integer('-' + (_num1 * _num2).big_number);
    } else if (num1_sign == '+' && num2_sign == '-') {
        _num2 = big_integer (b.substr (1, b.size() - 1));
        if (a[0] == '+') _num1 = big_integer (a.substr (1, a.size() - 1));
        else _num1 = num1;
        return big_integer('-' + (_num1 * _num2).big_number);
    } else {
        if (a[0] == '+') {
            _num1 = big_integer (a.substr (1, a.size() - 1));
            if (b[0] == '+') {
                _num2 = big_integer (b.substr (1, b.size() - 1));
            } else {
                _num2 = num2;
            }
            return _num1 * _num2;
        } else {
            _num1 = num1;
            if (b[0] == '+') {
                _num2 = big_integer (b.substr (1, b.size() - 1));
                return _num1 * _num2;
            }
        }
    }

    a = del_pre_zero(a);
    b = del_pre_zero(b);

    if (a == "0" || b == "0") {
        return big_integer ("0");
    }

    if (num1 < num2) {
        string tmp = a;
        a = b;
        b = tmp;
    }

    int i, j, index, len1 = a.size(), len2 = b.size();
    string ans(len1 + len2 - 1, '0');
    vector<int> ans_int(len1 + len2 - 1, 0);
    for (i = len1 - 1; i >= 0; --i) {
        for (j = len2 - 1; j >= 0; --j) {
            ans_int[i + j] += (a[i] - '0') * (b[j] - '0');
            //cout << "i + j = " << i + j << "\tans_int[i + j] = " << ans_int[i + j] << endl;
        }
    }
    int flag = 0;
    for (int i = ans_int.size() - 1; i >= 0; --i) {
        int tmp = ans_int[i];
        ans_int[i] = (tmp + flag) % 10;
        flag = (tmp+ flag) / 10;
    }

    for (int i = 0; i < ans_int.size(); ++i) ans[i] += ans_int[i];
    if (flag > 0) {
        char first = flag + '0';
        return big_integer (first + ans);
    }
    del_pre_zero(ans);
    return big_integer(ans);
}

big_integer operator*(const long long &num1, const big_integer &num2) {
    char p[10000];
    sprintf (p, "%lld", num1);
    return num2 * big_integer(string(p));
}

big_integer operator*(const big_integer &num1, const long long &num2) {
    char p[10000];
    sprintf (p, "%lld", num2);
    return    num1 * big_integer(string(p));
}