#include <iostream>
#include <vector>
#include <queue>

std::vector<bool> primes_below(size_t N)
{
  std::vector<bool> prime(N, true);

  for (size_t x = 3; x * x <= N; x += 2)
    if (prime[x])
      for (size_t m = x * x; m < N; m += 2 * x)
        prime[m] = false;

  return prime;
}

int main()
{
  size_t const N = 1'000'000;
  auto prime = primes_below(N);

  std::vector<size_t> primes;

  for (size_t x = 3; x < N; x += 2)
    if (prime[x])
      primes.push_back(x);

  size_t max = 0;

  size_t sum = 0;
  for (size_t idx = 2; idx < N; ++idx)
  {
    sum += primes[idx];

    if (sum >= N)
      break;

    if (prime[sum])
    {
      max = prime[sum];
      std::cout << sum << ' ' << primes[idx] << '\n';
    }
  }


}