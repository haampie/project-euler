
// Computes a^e mod m
// size_t powmod(size_t a, size_t e, size_t m)
// {
//     // repeat a^e mod m = a^(2q+r) mod m = (a^2 mod m)^q * (a^r mod m) mod m

//     size_t r = 1;

//     while (e > 1)
//     {
//         if (e % 2 == 1)
//             r = r * a % m;

//         a = a * a % m;
//         e /= 2;
//     }

//     return a * r % m;
// }

// bool potentially_prime(size_t n, size_t seed = 7)
// {
//     return powmod(seed, n - 1, n) == 1;
// }

// bool probabilistic_primality_test(size_t n)
// {
//     for (size_t p : {5, 7})
//         if (!potentially_prime(n, p))
//             return false;

//     return true;
// }