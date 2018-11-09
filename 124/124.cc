#include <iostream>
#include <vector>
#include <algorithm>
#include <iostream>
#include <utility>

std::vector<size_t> primes_below(size_t N)
{
    std::vector<bool> prime(N, true);

    for (size_t x = 3; x * x <= N; x += 2)
        if (prime[x])
            for (size_t m = x * x; m < N; m += 2 * x)
                prime[m] = false;

    std::vector<size_t> primes;

    primes.push_back(2);

    for (size_t x = 3; x < N; x += 2)
        if (prime[x])
            primes.push_back(x);

    return primes;
}

size_t rad(size_t n, std::vector<size_t> const &primes)
{
    size_t ret = 1;
    for (auto p : primes)
    {
        if (n == 1) break;
        if (n % p != 0) continue;
        ret *= p;
        do {n /= p;} while (n % p == 0);
    }

    return ret;
}

int main()
{
    using pair = std::pair<size_t,size_t>;
    size_t n = 100'000;
    size_t k = 10'000;
    auto primes = primes_below(n);
    std::vector<pair> v(n);

    for (size_t i = 1; i <= n; ++i)
        v[i - 1] = {i, rad(i, primes)};

    std::nth_element(v.begin(), v.begin() + k - 1, v.end(), [](pair &lhs, pair &rhs) {
        return (lhs.second < rhs.second ? true : (lhs.second > rhs.second ? false : lhs.first < rhs.first));
    });

    std::cout << v[k-1].first << '\n';
}