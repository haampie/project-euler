#include <iostream>
#include <algorithm>

int main()
{
    size_t sum = 0;
    for (size_t a = 3; a <= 1000; ++a)
    {
        size_t a2 = a * a;
        size_t value = std::max(2 * a, 2ul);

        for (size_t b = (6 * a) % a2; b != value; b = (b + 4 * a) % a2)
            if (b > value)
                value = b;

        sum += value;
    }

    std::cout << sum << '\n';
}