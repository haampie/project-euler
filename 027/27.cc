#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <tuple>

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

int main()
{
  size_t max = 0;
  std::pair<int64_t, size_t> maximizer;

  auto primes = primes_under(1'000'000);

  for (size_t b_idx = 0; primes[b_idx] < 1000; ++b_idx)
  {
    for (auto p : primes)
    {
      int64_t a = p - primes[b_idx] - 1;

      if (a <= -1000 || a >= 1000)
        break;

      for (size_t n = 2; n < 1'000'000; ++n) {
        int64_t num = n * n + a * n + primes[b_idx];

        if (num <= 0 || !std::binary_search(primes.begin(), primes.end(), num)) {
          if (n > max) {
            max = n;
            maximizer = std::make_pair(a, primes[b_idx]);
          }
          break;
        }
      }
    }
  }

  std::cout << '(' << maximizer.first << ',' 
    << maximizer.second << ") = " << max << '\n';

  for (size_t n = 0; n != max; ++n)
    std::cout << "n = " << n << ": " << (n * n + maximizer.first * n + maximizer.second) << '\n';
}