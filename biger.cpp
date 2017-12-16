#include "big_integer.h"
#include "utilities.h"
#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
#include <vector>
#include <unistd.h>

using namespace std;

//three '>'
bool operator> (const big_integer &num1, const big_integer &num2) {
    std::string a = num1.big_number;
    std::string b = num2.big_number;

    char num1_sign = get_num_sign(a);
    char num2_sign = get_num_sign(b);

    if (num1_sign == '+' && num2_sign == '+') {
        if (a[0] == '+') {
            a = a.substr(1, a.size() - 1);
            if (b[0] == '+') {
                b = b.substr(1, b.size() - 1);
            }
            return big_integer(a) > big_integer(b);
        } else {
            if(b[0] == '+') {
                b = b.substr(1, b.size() - 1);
                return big_integer(a) > big_integer(b);
            }
        }
    } else if (num1_sign == '+' && num2_sign == '-') {
        if (num1 == num2) return false;
        else return true;
    } else if (num1_sign == '-' && num2_sign == '+') {
        return false;
    } else {
        a = a.substr(1, a.size() - 1);
        b = b.substr(1, b.size() - 1);
        a = del_pre_zero(a);
        b = del_pre_zero(b);
        if (a == b) return false;
        else return !(big_integer(a) > big_integer(b));
    }

    a = del_pre_zero(a);
    b = del_pre_zero(b);
    
    if (a.size() > b.size()) return true;
    else if (a.size() < b.size()) return false;
    else {
        for (int i = 0; i < a.size(); ++i) {
            if(a[i] > b[i]) return true;
            else if (a[i] < b[i]) return false;
        }
        return false;
    }
}

bool operator> (const big_integer &num1, const long long &num2) {
    char p[10000];
    sprintf (p, "%lld", num2);
    return num1 > (big_integer(string(p)));
}

bool operator> (const long long &num1, const big_integer &num2) {
    char p[10000];
    sprintf (p, "%lld", num1);
    return big_integer(string(p)) > num2;
}