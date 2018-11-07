#include <vector>
#include <iostream>
#include <algorithm>

int64_t count(int64_t n)
{
    std::vector<size_t> v(n + 1, 0);

    for (size_t k = 2; k <= n; ++k)
    {
        // Don't place a brick
        v[k] = v[k - 1];

        // Place a brick of length b
        for (size_t b = 2; b <= std::min((size_t)4, k); ++b)
        {
            v[k] += 1 + v[k - b];
        }
    }

    return v[n] + 1;
}

int main()
{
    std::cout << count(50) << '\n';
}