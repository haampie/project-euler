#include <iostream>
#include <set>
#include <algorithm>
#include <iterator>

size_t decr(size_t depth = 4, size_t digit = 9)
{
    size_t total = 1;

    if (depth != 0)
        for (int i = digit; i >= 0; --i)
            total += decr(depth - 1, i);

    return total;
}

size_t incr(size_t depth = 4, size_t digit = 1)
{
    size_t total = 1;

    if (depth != 0)
        for (size_t i = digit; i < 10; ++i)
            total += incr(depth - 1, i);

    return total;
}

bool is_bouncy(size_t n)
{    
    bool up = false;
    bool down = false;
    
    size_t prevd = n % 10;
    n /= 10;

    while (n)
    {
        size_t next_d = n % 10;

        if (next_d > prevd) up = true;
        else if (next_d < prevd) down = true;
        if (up && down) return true;

        prevd = next_d;
        n /= 10;
    }

    return false;
}

int main()
{
    incr(5);
    // for (size_t len = 1; len < 30; ++len)
    // {
    //     size_t multiple = 10 * len + 2;
    //     size_t total = incr(len) + decr(len) - multiple;
    //     std::cout << total << '\n';
    // }
}