#include <iostream>

size_t get_numerator(size_t taken = 0, size_t product = 1, size_t index = 1)
{
    if (taken == 7 || index == 16)
        return 0;

    size_t sum = 0;
    
    // take this one
    if (taken < 7)
    {
        sum += product * index;
        sum += get_numerator(taken + 1, product * index, index + 1);
    }

    // drop this one
    sum += get_numerator(taken, product, index + 1);

    return sum;
}

int main()
{
    size_t denominator = 1;
    for (size_t i = 2; i <= 16; ++i)
        denominator *= i;

    size_t numerator = get_numerator() + 1;

    std::cout << (double)(denominator - numerator) / (double)numerator << '\n';

    // (1 - p) - p * m > 0
    // (1 - p) > p * m
    // m < (1 - p) / p
    // m < (den-num)/num
}