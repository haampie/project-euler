#include <iostream>
#include <algorithm>
#include <array>
#include <numeric>

size_t count(size_t length)
{
    size_t sum = 0;
    std::array<size_t, 10> f;
    std::fill(f.begin(), f.end(), 1);

    for (size_t i = 0; i < length; ++i)
    {
        for (auto d : f)
            sum += 2 * d;

        sum -= f[9];

        std::partial_sum(f.begin(), f.end(), f.begin());
    }

    return sum - 10 * length;
}

int main()
{
    std::cout << count(100) << '\n';
}