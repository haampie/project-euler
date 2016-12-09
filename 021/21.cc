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
  size_t const cap = 10000;
  auto primes = primes_under(cap);

  std::vector<size_t> proper_divisor_sum(cap, 0);

  for (size_t n = 1; n < cap; ++n)
  {
    // std::cout << "n = " << n << ": ";

    for (auto div : divisors(n, primes))
    {
      if (div != n)
        proper_divisor_sum[n] += div;

      // std::cout << div << ' ';
    }

    // std::cout << " == " << proper_divisor_sum[n] << '\n';
  }

  size_t sum = 0;

  for (size_t n = 1; n < cap; ++n)
  {
    if (proper_divisor_sum[n] < cap && proper_divisor_sum[n] != n && proper_divisor_sum[proper_divisor_sum[n]] == n)
    {
      std::cout << '(' << n << ", " << proper_divisor_sum[n] << ")\n";
      sum += n;
    }
  }

  std::cout << sum << '\n';
}