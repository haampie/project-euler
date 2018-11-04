#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <limits>

std::vector<size_t> primes_under(size_t N)
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

// 1/x + 1/y = 1/n <=> (x-n)(y-n) = n^2
// d(n) = number of divisors of n^2 = number of solution pairs {x,y}
// if n = p_1^a_1 * ... * p_l^a_l then
// d(n) = (a_1 + 1) * ... * (a_l + 1)
// d(n^2) = (2a_1 + 1) * ... & (2a_l + 1)
// x = y only if x = y = 2n of course,
// unique solutions are hence S(n) = ((2a_1 + 1) * ... * (2a_l + 1) - 1) / 2 + 1.

template<class T>
void find(size_t M, size_t prod, size_t n, T prime, T begin, T count, size_t &best_n, size_t max = 100)
{    
    if (prod > 2 * M - 1) {
        if (n < best_n)
            best_n = n;
        
        std::cout << "n = " << n << ": ";
        std::copy(begin, count, std::ostream_iterator<size_t>(std::cout, " "));
        std::cout << '\n';
        return;
    }

    for (size_t i = 1; i <= max; ++i)
    {
        n *= *prime;
        if (n > best_n)
            return;
        *count = i;
        find(M, prod * (2 * i + 1), n, prime + 1, begin, count + 1, best_n, i);
    }
}

int main()
{
    // just generate enough prime numbers & count...
    std::vector<size_t> primes = primes_under(100);
    std::vector<size_t> count(primes.size(), 0);
    size_t best_n = std::numeric_limits<size_t>::max();

    find(1'000, 1, 1, primes.begin(), count.begin(), count.begin(), best_n);
}