#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

size_t count(size_t n)
{
    std::vector<int64_t> v(n + 1, 0);

    for (int64_t k = 3; k <= n; ++k)
    {
        // There are k-2 bricks of length 3 to k.
        v[k] += k - 2;

        // Then the remainder can be filled
        for (int64_t l = 1; l < k - 3; ++l)
            v[k] += v[l];

        // And then there is the situation where you don't place a brick at `k`
        v[k] += v[k - 1];
    }

    return v[n] + 1; // also count the empty one.
}

int main()
{
    std::cout << count(50) << '\n';
}