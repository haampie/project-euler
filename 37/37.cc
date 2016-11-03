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

size_t reverse(size_t N)
{
  size_t reverse = 0;

  while (N != 0)
  {
    reverse *= 10;
    reverse += N % 10;
    N /= 10;
  }

  return reverse;
}

bool truncatable_back(size_t N, std::vector<size_t> const &primes)
{
  while (N >= 10)
  {
    if (!std::binary_search(primes.begin(), primes.end(), N / 10))
      return false;

    N /= 10;
  }

  return true;
}

bool truncatable_front(size_t N, std::vector<size_t> const &primes)
{
  while (N >= 10)
  {
    size_t chop = reverse(reverse(N) / 10);
    if (!std::binary_search(primes.begin(), primes.end(), chop))
      return false;

    N = chop;
  }

  return true;
}

int main()
{
  size_t const cap = 3'000'000;
  auto primes = primes_below(cap);

  for (size_t idx = 4; idx != primes.size(); ++idx)
    if (truncatable_back(primes[idx], primes) && truncatable_front(primes[idx], primes))
      std::cout << primes[idx] << '\n';
}