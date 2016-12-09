#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <tuple>

bool is_permutation(size_t a, size_t b)
{
  char digits[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  char total = 0;

  for (; a != 0; a /= 10)
  {
    ++digits[a % 10];
    ++total;
  }

  for (; b != 0; b /= 10)
  {
    if (digits[b % 10]-- == 0)
      return false;
    --total;
  }

  return total == 0;
}

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
  auto primes = primes_below(10'000);

  std::tuple<double, size_t, size_t> min{10.0, 0, 0};


  for (size_t x = 0; x < primes.size(); ++x)
    for (size_t y = x + 1; y < primes.size(); ++y)
    {
      if (primes[x] * primes[y] > 10'000'000)
        break;

      double ratio = static_cast<double>(primes[x] * primes[y]) / ((primes[x] - 1) * (primes[y] - 1));

      if (ratio < std::get<0>(min) && is_permutation(primes[x] * primes[y], (primes[x] - 1) * (primes[y] - 1)))
      {
        min = std::make_tuple(ratio, primes[x], primes[y]);
        std::cout << primes[x] << ' ' << primes[y] << '\n';
      }
    }
}