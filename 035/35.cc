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

bool circular(size_t p, std::vector<size_t> const &primes)
{
  size_t copy = p;
  size_t rotations = 0;
  size_t factor = 1;

  while (copy >= 10)
  {
    ++rotations;
    factor *= 10;
    copy /= 10;
  }

  for (size_t rotation = 0; rotation != rotations; ++rotation)
  {
    p = p / 10 + factor * (p % 10);

    if (!std::binary_search(primes.begin(), primes.end(), p))
      return false;
  }

  return true;
}

int main()
{
  size_t count = 0;
  auto primes = primes_below(1'000'000);

  for (size_t p : primes)
  {
    if (circular(p, primes))
    {
      ++count;
      std::cout << p << '\n';
    }
  }

  std::cout << count << '\n';
}