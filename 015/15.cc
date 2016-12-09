#include <iostream>

size_t choose(size_t n, size_t k)
{
  if (k == 0)
    return 1;

  return n * choose(n - 1, k - 1) / k;
}

int main()
{
  std::cout << choose(40, 20) << '\n';
}