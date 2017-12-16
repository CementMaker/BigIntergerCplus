#include <cstdio>
#include <cstring>
#include <iostream>
#include "big_integer.h"

using namespace std;

int main()
{
	string a = "787", b = "23423423";
	big_integer aa(a);
	big_integer bb(b);
	big_integer cc(aa + bb);
}