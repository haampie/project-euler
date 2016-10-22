#include <iostream>
#include <vector>

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

std::vector<size_t> prime_divisors(size_t N, std::vector<size_t> const &primes)
{
  size_t idx = 0;
  std::vector<size_t> list;

  while (N != 1)
  {
    if (N % primes[idx] != 0)
    {
      ++idx;
      continue;
    }

    N /= primes[idx];
    list.push_back(primes[idx]);
  }

  return list;
}

size_t num_divisors(size_t N, std::vector<size_t> const &primes)
{
  size_t idx = 0;
  size_t count = 1;

  while (N != 1)
  {
    if (N % primes[idx] == 0)
    {
      size_t multiplier = 1;

      do
      {
        N /= primes[idx];
        ++multiplier;
      } while (N % primes[idx] == 0);
      
      count *= multiplier;
    }

    ++idx;
  }

  return count;
}

void output(size_t fst, size_t snd, std::vector<size_t> const &primes)
{ 
  for (size_t d : prime_divisors(fst, primes)) {
    std::cout << d << ' ';
  }
  std::cout << ", ";
  for (size_t d : prime_divisors(snd, primes)) {
    std::cout << d << ' ';
  }
  std::cout << '\n';
}

int main()
{
  size_t const cap = 200'000;
  auto primes = primes_under(cap);

  size_t previous = 0;
  size_t max = 0;

  // n is even, n + 1 even.
  for (size_t n = 2; n < cap; n += 2)
  {
    size_t lhs = num_divisors(n / 2, primes);
    size_t rhs = num_divisors(n + 1, primes);
    size_t prev = previous * lhs;
    size_t curr = lhs * rhs;

    if (prev > max) {
      max = prev;
      std::cout << "New max for n = " << n - 1 << " (" << max << ")\n";
      output(n - 1, n / 2, primes);
    }

    if (curr > max) {
      max = curr;
      std::cout << "New max for n = " << n << " (" << max << ")\n";
      output(n / 2, n + 1, primes);
    }

    if (max > 500)
      break;

    previous = rhs;
  }
}