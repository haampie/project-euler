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

int main()
{
  const size_t max = 100;
  auto primes = primes_below(max + 1);

  std::vector<std::vector<size_t>> count;

  for (size_t y = 0; y <= max; ++y)
    count.push_back(std::vector<size_t>(max + 1, 0));

  count[0][0] = 1;

  for (size_t y = 1; y <= max; ++y)
  {
    for (size_t x = 1; x <= y; ++x)
      for (auto p = primes.begin(); *p <= x; ++p)
        count[y][x] += count[y - *p][std::min(*p, y - *p)];

    if (count[y][y - 1] > 5000)
    {
      std::cout << y << '\n';
      break;
    }
  }
}