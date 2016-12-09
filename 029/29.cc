#include <iostream>

int main()
{
  size_t total = 0;
  for (size_t num = 2; num != 100'000'000; ++num)
  {
    size_t sum = 0;
    size_t copy = num;
    while (copy != 0)
    {
      size_t digit = copy % 10;
      copy /= 10;
      sum += (digit * digit) * digit * (digit * digit);
    }

    if (sum == num)
    {
      total += sum;
      std::cout << num << '\n';
    }
  }

  std::cout << '\n' << total << '\n';
}