#include <iostream>
#include <random>

bool rabin_miller(size_t n, size_t k)
{
  if (n == 2 || n == 3) return true;
  if (n <= 1 || n % 2 == 0) return false;

  size_t s = 0;
  size_t d = n - 1;

  while (d % 2 == 0)
  {
    ++s;
    d /= 2;
  }

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distr(2, n - 2);

  for (size_t idx = 0; idx != k; ++idx)
  {
    size_t a = distr(gen);
    size_t x = 1;

    for (size_t times = 0; times != d; ++times)
      x = (a * x) % n;

    if (x == 1 || x == n - 1)
      continue;

    bool quit = true;

    for (size_t r = 1; r <= s - 1; ++r)
    {
      x = x * x % n;

      if (x == 1)
        continue;

      if (x == n - 1) {
        quit = false;
        break;
      }
    }

    if (quit)
      return false;
  }

  return true;
}

int main()
{
  for (size_t idx = 1; idx < 100; idx += 2)
    if (rabin_miller(idx, 5))
      std::cout << idx << '\n';
}