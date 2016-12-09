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

size_t num_divisors(size_t N, std::vector<size_t> const &primes)
{
  size_t idx = 0;
  size_t count = 0;

  while (N != 1)
  {
    if (N % primes[idx] == 0)
    {
      do
      {
        N /= primes[idx];
      } while (N % primes[idx] == 0);
      
      ++count;
    }

    ++idx;
  }

  return count;
}

size_t print_divisors(size_t N, std::vector<size_t> const &primes)
{
  size_t idx = 0;
  size_t count = 0;

  while (N != 1)
  {
    if (N % primes[idx] == 0)
    {
      do
      {
        N /= primes[idx];
      } while (N % primes[idx] == 0);
      
      std::cout << primes[idx] << ' ';
      ++count;
    }

    ++idx;
  }

  return count;
} 

int main()
{
  const size_t length = 4;
  const size_t max = 1'000'000;
  auto primes = primes_below(max);

  for (size_t num = 647; num != max - length; ++num)
  {
    size_t k = 0;

    for (; k != length && num_divisors(num + k, primes) >= length; ++k);

    if (k == length) {
      std::cout << num << '\n';

      print_divisors(num, primes); std::cout << '\n';
      print_divisors(num + 1, primes); std::cout << '\n';
      print_divisors(num + 2, primes); std::cout << '\n';
      print_divisors(num + 3, primes); std::cout << '\n';
      break;
    }

    num += k + 1;
  }

}