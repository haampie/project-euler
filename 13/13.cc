#include <iostream>
#include <vector>

int main()
{
  const size_t size = 50;
  const size_t total = 100;

  std::vector<size_t> sum(size + 4, 0);

  char c;

  for (size_t inputs = 0; inputs != total; ++inputs)
  {
    for (size_t idx = size; idx > 0; --idx)
    {
      std::cin >> c;
      std::cout << c << '\n';
      size_t num = c - '0';

      sum[idx - 1] += num;

      for (size_t digit = idx - 1; sum[digit] >= 10; ++digit)
      {
        sum[digit] -= 10;
        ++sum[digit + 1];
      }
    }
  }

  for (auto it = sum.rbegin(); it != sum.rend(); ++it)
  {
    std::cout << *it;
  }
  std::cout << '\n';
}