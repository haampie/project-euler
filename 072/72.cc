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

size_t count(
  std::vector<size_t>::const_iterator factor,
  std::vector<size_t>::const_iterator last, 
  size_t denominator, 
  size_t totient, 
  size_t const N
)
{
  size_t prime_factor = *factor;

  // No factors left or the denominator gets too high.
  if (factor == last || denominator * prime_factor > N)
    return totient;

  size_t sum = 0;

  // Skip this prime number
  sum += count(factor + 1, last, denominator, totient, N);

  // Or include this prime number 1 or more times.
  size_t totient_factor = prime_factor - 1;
  denominator *= prime_factor;

  while (denominator <= N)
  {
    sum += count(factor + 1, last, denominator, totient * totient_factor, N);
    denominator *= prime_factor;
    totient_factor *= prime_factor;
  }

  return sum;
}

int main()
{
  auto primes = primes_below(1'000'001);

  size_t fractions = count(primes.begin(), primes.end(), 1, 1, 1'000'000);

  // Fix off by one error, since totient(1) = 1 and not 0.
  std::cout << fractions - 1 << '\n';
}