#include <iostream>
#include <vector>

int main()
{
  const size_t search = 10'001;
  const size_t num = 1'000'000;
  std::vector<bool> prime(num, true);

  for (size_t x = 3; x * x <= num; x += 2)
    if (prime[x])
      for (size_t m = x * x; m < num; m += 2 * x)
        prime[m] = false;

  size_t count = 1;

  for (size_t x = 3; x < num; x += 2)
  {
    if (prime[x] && ++count == search)
    {
      std::cout << x << '\n';
      break;
    }
  }
}