#include <iostream>

size_t collatz(size_t N)
{
  size_t steps = 0;
  while (N != 1)
  {
    ++steps;
    N = (N % 2 == 0 ? N / 2 : 3 * N + 1);
  }

  return steps;
}

int main()
{
  size_t max = 0;
  size_t idx_max = 0;

  for (size_t idx = 1; idx != 1'000'000; ++idx)
  {
    size_t length = collatz(idx);
    if (length > max)
    {
      max = length;
      idx_max = idx;
      std::cout << idx_max << ": " << max << '\n';
    }
  }
}