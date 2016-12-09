#include <iostream>

size_t pow(size_t base, size_t exp)
{
  size_t num = 1;

  for (size_t idx = 0; idx != exp; ++idx, num *= base);

  return num;
}

int main()
{
  size_t min = 1;

  for(size_t l = 1; l != 30; ++l, min *= 10)
  {
    std::cout << "length = " << l << '\n';

    for(size_t idx = 1; idx != 10; ++idx)
    {
      size_t num = pow(idx, l);
      if (num >= min && num < 10 * min)
        std::cout << pow(idx, l) << '\n';
    }
  }
}