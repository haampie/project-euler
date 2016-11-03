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

bool pandigital(size_t N)
{
  std::vector<size_t> q{true, false, false, false, 
    false, false, false, false, false, false};

  size_t count = 0;

  while (N != 0)
  {
    if (q[N % 10])
      return false;

    q[N % 10] = true;
    N /= 10;
    ++count;
  }

  for (size_t idx = 0; idx <= count; ++idx)
    if (!q[idx])
      return false;

  return true;
}

int main()
{
  auto primes = primes_below(10'000'000);

  std::cout << primes.size() << '\n';

  for (auto it = primes.rbegin(); it != primes.rend(); ++it)
  {
    if (pandigital(*it))
    {
      std::cout << *it << '\n';
      break;
    }
  }
}