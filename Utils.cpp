//
// Created by goeran on 12.01.2023.
//

#include <iostream>

// bitwise interlacing of x and y
int z_function(int x, int y)
{
    int z = 0;
    for (int i = 0; i < 32; i++)
    {
        z |= (x & 1) << (2 * i);
        z |= (y & 1) << (2 * i + 1);
        x >>= 1;
        y >>= 1;
    }
    return z;
}

// next power of 2
int next_power_of_two(int x)
{
    int y = 1;
    while (y < x)
        y *= 2;
    return y;
}

// previous power of 2
int prev_power_of_two(int x)
{
    int y = 1;
    while (y < x)
        y *= 2;
    return y / 2;
}

void print_bool(bool cond) {
    if (cond) {
        std::cout << "True\n";
    } else {
        std::cout << "False\n";
    }
}