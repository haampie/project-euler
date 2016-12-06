#include <iostream>
#include <vector>
#include <map>

using it = std::vector<size_t>::const_iterator;

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

size_t construct(it current, it last, size_t product, size_t sum, size_t const N)
{

  // Sum of proper divisors is too large
  if (sum > N + product)
    return 1;

  // Last prime factor or too large number.
  if (current == last || product * (*current) > N)
    return 0;

  size_t total = 0;

  // Multiply by prime factor as long as product <= N
  for (size_t sum_factor = 1, multiplier = 1; product <= N; product *= *current)
  {
    total += construct(current + 1, last, product, sum_factor * sum, N);
    multiplier *= *current;
    sum_factor += multiplier;
  }

  return total;
}

int main()
{
  size_t const N = 1'000'000;
  auto primes = primes_below(N);
  std::cout << construct(primes.begin(), primes.end(), 1, 1, N) << '\n';
}