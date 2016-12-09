#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

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

void sum_of_squares(size_t square)
{
  size_t integer_part = 1;

  for (; integer_part * integer_part + 2 * integer_part < square; ++integer_part);

  std::vector<size_t> expansion;
  expansion.push_back(integer_part);

  size_t m = 0;
  size_t d = 1;

  for (size_t idx = 0; expansion[idx] != 2 * expansion[0]; ++idx)
  {
    m = d * expansion[idx] - m;
    d = (square - m * m) / d;
    size_t sum_sqrs = m*m + d*d;
    
    if (sum_sqrs == square)
    {
      // std::cout << m << "^2 + " << d << "^2 = " << sum_sqrs << '\n';
      return;
    }
    
    expansion.push_back((integer_part + m) / d);
  }
}



int main()
{
  auto primes = primes_below(1'000'000);

  for (size_t prime : primes)
    if (prime % 4 == 1)
      sum_of_squares(prime);
}