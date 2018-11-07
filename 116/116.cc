#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

int64_t first_k(int64_t min = 1'000'000, int64_t b = 50)
{
    std::vector<int64_t> v(b, 0);

    for (int64_t k = b;; ++k)
    {
        // There are k - b + 1 bricks of length b to k.
        int64_t vk = k - b + 1;

        // Then the remainder can be filled
        for (int64_t l = 1; l < k - b; ++l)
            vk += v[l];

        // And then there is the situation where you don't place a brick at `k`
        vk += v[k - 1];

        if (vk + 1 > min)
            return k;
 
        v.push_back(vk);
    }

    return -1;
}

int main()
{
    std::cout << first_k(1'000'000, 50) << '\n';
}