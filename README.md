# big_integer
    C++ 大整数的加减乘除


    utilities.h
    两个函数  get_num_sign --------> 获取数的正负号
              del_pro_zero --------> 取出数字（string）的首部的0

    big_integer.h 声明各种需要重载的与运算符号;
        重载符号有：+, -, multi, /, ==, =, % , >= , >, <= , <
        实现大整数的排序（快速排序）

    big_integer.cc 实现各种重载，主要是高精度加减乘除，还有快排。


    运算速度还行，仅做参考
