#include <vector>
#include <iostream>
#include <algorithm>

size_t count(size_t n, size_t b)
{
    std::vector<size_t> v(n + 1, 0);

    for (size_t k = b; k <= n; ++k)
        v[k] = 1 + v[k - b] + v[k - 1];

    return v[n];
}

int main()
{
    std::cout << count(50, 2) +  count(50, 3) + count(50, 4) << '\n';
}