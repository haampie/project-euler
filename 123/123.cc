#include <iostream>
#include <vector>
#include <algorithm>

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

int main()
{
    auto primes = primes_below(10'000'000);

    for (size_t n = 1; n <= primes.size(); n += 2)
    {
        size_t p = primes[n - 1];
        size_t value = (2 * n * p) % (p * p);
        // std::cout << n << ' ' << p << ' ' << value << '\n';

        if (value > 10'000'000'000)
        {
            std::cout << n << '\n';
            break;
        }
    }
}
