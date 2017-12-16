#include "big_integer.h"
#include "utilities.h"
#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
#include <vector>
#include <unistd.h>

using namespace std;

//three '%'
big_integer operator%(const big_integer &num1, const big_integer &num2) {
    big_integer num = num1 / num2;
    return num1 - (num * num2);
}

big_integer operator%(const big_integer &num1, const long long &num2) {
    char tmp[10000];
    sprintf (tmp, "%lld", num2);
    return  num1 % big_integer(string(tmp));
}

big_integer operator%(const long long &num1, const big_integer &num2) {
    char p[10000];
    sprintf (p, "%lld", num1);
    return big_integer(string(p)) % num2;
}