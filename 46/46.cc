#include <iostream>
#include <vector>

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
  const size_t max = 1'000'000;
  std::vector<bool> odds(max, false);
  auto primes = primes_below(max);

  for (auto p : primes)
    for (size_t k = 0; p + 2 * k * k < max; ++k)
      odds[p + 2 * k * k] = true;

  for (size_t odd = 1; odd < max; odd += 2)
    if (odds[odd] == false)
      std::cout << odd << '\n';

}