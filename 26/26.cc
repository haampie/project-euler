#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>

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

size_t remainder(size_t base, size_t exp, size_t divider)
{
  size_t other_term = 1;

  while (exp != 1) {
    if (exp % 2 == 0) {
      base = base * base % divider;
      exp /= 2;
    } else {
      other_term = other_term * base % divider;
      --exp;
    }
  }

  return base * other_term % divider;
}

int main()
{
  size_t max = 0;
  size_t max_index = 0;
  size_t const cap = 1'000;
  auto primes = primes_under(cap);

  for (size_t prime : primes)
  {
    if (prime == 2 || prime == 5)
      continue;

    for (size_t power = 1; power < 10000; ++power)
    {
      if (remainder(10, power, prime) == 1)
      {
        if (power > max)
        {
          max = power;
          max_index = prime;
        }
        break;
      }
    }
  }

  std::cout << max_index << " has cycle " << max << '\n';
}