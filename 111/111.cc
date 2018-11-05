#include <iostream>
#include <vector>
#include <numeric>

struct IsPrime
{
    std::vector<size_t> testers;

    IsPrime(size_t n) : testers()
    {
        // Generate test primes
        std::vector<bool> prime(n, true);

        for (size_t x = 3; x * x <= n; x += 2)
            if (prime[x])
                for (size_t m = x * x; m < n; m += 2 * x)
                    prime[m] = false;

        testers.push_back(2);

        for (size_t x = 3; x < n; x += 2)
            if (prime[x])
                testers.push_back(x);
    }

    bool operator()(size_t candidate) const
    {
        for (auto p : testers)
        {
            if (p * p > candidate)
                return true;

            if (candidate % p == 0)
                return false;
        }
        
        return true;
    }
};

template<class Handler>
bool multidigit_prime_walker(IsPrime const &is_prime, Handler &handle, 
                             size_t fill = 1, size_t length = 10, size_t different = 2, 
                             bool allow_zero = false, size_t num = 0)
{
    // Created a number of the required length
    if (length == 0)
    {
        bool prime = is_prime(num);

        if (prime)
            handle(num);
        
        return prime;
    }

    // Number not yet of required length, add a digit
    bool found = false;

    // Append a different number than `fill`
    if (different > 0)
        for (size_t j = (allow_zero ? 0 : 1); j < 10; ++j)
            if (j != fill)
                found |= multidigit_prime_walker(is_prime, handle, fill, length - 1, different - 1, true, 10 * num + j);
    
    // Add a `fill` number.
    if (different != length && (fill != 0 || allow_zero))
        found |= multidigit_prime_walker(is_prime, handle, fill, length - 1, different, true, 10 * num + fill);

    return found;
}

int main()
{
    // For primality test
    IsPrime is_prime(100'000);

    // To sum the prime numbers found
    size_t sum = 0;
    auto handle = [&](size_t prime) {
        sum += prime;
    };

    for (size_t digit = 0; digit < 10; ++digit)
        for (size_t i = 1; !multidigit_prime_walker(is_prime, handle, digit, 10, i); ++i);

    std::cout << sum << '\n';
}