#include <bitset>
#include <vector>
#include <unordered_set>
#include <iostream>
#include <algorithm>
#include <iomanip>

constexpr size_t N = 30;

int main()
{
    std::vector<std::unordered_set<std::bitset<N>>> s(N);

    // Initialized with 0 products and just `1` being used
    s[0].insert(1);
    
    for (size_t n = 2; n <= N; ++n)
    {
        std::cout << std::setw(3) << n << ": ";
        for (size_t j = 1; j <= n / 2; ++j)
        {
            size_t k = n - j;

            // n is being used.
            for (auto &lhs : s[j - 1])
            {
                for (auto &rhs : s[k - 1])
                {
                    auto used = lhs | rhs; used.set(n - 1);
                    s[n - 1].insert(used);
                }
            }
        }

        auto minel = std::min_element(s[n - 1].begin(), s[n - 1].end(), [](std::bitset<N> const &lhs, std::bitset<N> const &rhs){
            return lhs.count() < rhs.count();
        });

        for (size_t digit = 0; digit < n; ++digit)
            if (minel->test(digit))
                std::cout << digit + 1 << ' ';

        std::cout << '\n';
    }
}