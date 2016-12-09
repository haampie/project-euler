#include <iostream>
#include <vector>

int main()
{
  const size_t divider = 10'000'000'000ul;

  size_t sum = 0;

  for (size_t n = 1; n != 1001; ++n)
  {
    size_t prod = n;
    for (size_t i = 1; i != n; ++i)
      prod = (n * prod) % divider;

    sum = (sum + prod) % divider;
  }

  std::cout << sum << '\n';
}