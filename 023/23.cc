#include <iostream>
#include <vector>

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

std::vector<size_t> divisors(size_t N, std::vector<size_t> const &primes)
{
  size_t idx = 0;
  std::vector<size_t> list{1};

  while (N != 1)
  {
    // Not divisable
    if (N % primes[idx] != 0)
    {
      ++idx;
      continue;
    }

    // Count occurences.
    size_t occurences = 0;

    do
    {
      N /= primes[idx];
      ++occurences;
    } while (N % primes[idx] == 0);

    size_t multiple = 1;
    size_t previous_total = list.size();
    for (size_t i = 0; i != occurences; ++i)
    {
      multiple *= primes[idx];
      for (size_t j = 0; j != previous_total; ++j)
      {
        list.push_back(multiple * list[j]);
      }
    }
  }

  return list;
}

int main()
{
  size_t const cap = 28124;
  auto primes = primes_under(cap);

  std::vector<size_t> abundant;

  for (size_t n = 1; n < cap; ++n)
  {
    size_t sum = 0;
    for (auto div : divisors(n, primes))
      if (div != n)
        sum += div;

    if (sum > n)
      abundant.push_back(n);
  }

  std::vector<bool> sumOfTwo(cap, false);
  
  for (size_t lhs = 0; lhs != abundant.size(); ++lhs)
    for (size_t rhs = 0; rhs <= lhs && abundant[lhs] + abundant[rhs] < cap; ++rhs)
      sumOfTwo[abundant[lhs] + abundant[rhs]] = true;

  size_t total = 0;
  for (size_t idx = 1; idx != cap; ++idx)
    if (!sumOfTwo[idx])
      total += idx;

  std::cout << total << '\n';
}