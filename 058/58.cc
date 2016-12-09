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

bool is_prime(size_t candidate, std::vector<size_t> const &primes)
{
  for (size_t idx = 0; primes[idx] * primes[idx] <= candidate; ++idx)
    if (candidate % primes[idx] == 0)
      return false;

  return true;
}

int main()
{
  auto primes = primes_below(30'000);

  size_t step = 2;

  for (size_t corner = 9, found = 3; 10 * found > 2 * step + 1; corner += step)
  {
    step += 2;

    for (size_t idx = 0; idx != 3; ++idx) {
      corner += step;

      if (is_prime(corner, primes)) 
        ++found;
    }
  }

  std::cout << step + 1 << '\n';
}