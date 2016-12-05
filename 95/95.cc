#include <iostream>
#include <vector>
#include <map>

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

void construct(
  std::vector<size_t>::const_iterator current,
  std::vector<size_t>::const_iterator last,
  std::map<size_t, size_t> &factors,
  size_t product,
  size_t sum,
  size_t const N
)
{
  size_t prime_factor = *current;

  // No factors left or the denominator gets too high.
  if (current == last || product > N)
  {
    std::cout << product << " = ";
    for (const auto &factor : factors)
      for (size_t idx = 0; idx < factor.second; ++idx)
        std::cout << factor.first << ' ';

    std::cout << '(' << sum << ")\n";
    return;
  }

  // Skip this prime number
  construct(current + 1, last, factors, product, sum, N);

  // Or include this prime number 1 or more times.
  factors[prime_factor] = 1;
  size_t sum_factor = prime_factor + 1;
  size_t multiplier = prime_factor;

  for (product *= prime_factor; product <= N; product *= prime_factor)
  {
    construct(current + 1, last, factors, product, sum_factor * sum, N);
    ++factors[prime_factor];
    multiplier *= prime_factor;
    sum_factor += multiplier;
  }
  factors.erase(prime_factor);
}

int main()
{
  size_t const N = 100'000;
  auto primes = primes_below(N);

  std::map<size_t, size_t> guys;
  construct(primes.begin(), primes.end(), guys, 1, 1, N);
}