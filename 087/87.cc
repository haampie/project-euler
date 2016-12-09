#include <iostream>
#include <vector>
#include <set>

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
  const size_t N = 50'000'000;

  auto primes = primes_below(7072);
  std::set<size_t> combis;

  for (auto p1 : primes)
  {
    size_t fourth = p1 * p1 * p1 * p1;

    if (fourth > N)
      break;

    for (auto p2 : primes)
    {
      size_t cube = p2 * p2 * p2 + fourth;

      if (cube > N)
        break;

      for (auto p3 : primes)
      {
        size_t square = p3 * p3 + cube;

        if (square > N)
          break;

        combis.insert(square);
      }
    }
  }

  std::cout << combis.size() << '\n';
}