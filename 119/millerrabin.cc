#include <iostream>

bool is_prime_like(size_t a, size_t d, size_t n)
{
    // Compute a^d mod n
    size_t x = a; size_t i = 1;
    for (; 2 * i <= d; x = x * x % n, i *= 2); // repeated squaring
    for (; i < d; x = a * x % n, ++i);         // remainder

    if (x == 1 || x == n - 1) return true;

    for (; d != n - 1; d *= 2)
    {
        x = x * x % n;
        if (x == n - 1) return true;
    }

    return false;
}

bool is_probably_prime(size_t n)
{
    if (n == 2 || n == 3 || n == 5 || n == 7) return true; 
    if (n <= 8 || n % 2 == 0) return false;

    // n - 1 = 2^r * d
    size_t r = 1; size_t d = (n - 1) / 2;
    for (; d % 2 == 0; ++r, d /= 2);

    for (size_t a : {2, 3, 5, 7})
        if (!is_prime_like(a, d, n))
            return false;

    return true;
}

int main()
{
    size_t cnt = 0;
    for (size_t i = 0; i < 100'000; ++i)
        if (is_probably_prime(i))
            ++cnt;

    std::cout << cnt;
}