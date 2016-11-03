#include <iostream>
#include <vector>

int main()
{
  std::vector<size_t> factorial(10, 1);

  for (size_t idx = 1, product = 1; idx != 10; ++idx)
  {
    product *= idx;
    factorial[idx] = product;
  }

  for (size_t num = 1; num <= 2'540'160; ++num)
  {
    size_t copy = num;
    size_t sumoffacts = 0;

    while (copy != 0)
    {
      sumoffacts += factorial[copy % 10];
      copy /= 10;
    }

    if (sumoffacts == num)
      std::cout << num << '\n';
  }
}