#include <iostream>
#include <vector>

int main()
{
  std::vector<unsigned char> digits(1, 1);

  for (size_t idx = 0; idx != 1000; ++idx)
  {
    for (size_t back = digits.size(); back > 0; --back)
    {
      digits[back - 1] *= 2;

      for (size_t digit = back - 1; digits[digit] >= 10; ++digit)
      {
        size_t times = digits[digit] / 10;
        digits[digit] %= 10;

        if (digit + 1 == digits.size())
          digits.push_back(times);
        else
          digits[digit + 1] += times;
      }
    }
  }

  size_t sum = 0;
  
  for (size_t idx = 0; idx != digits.size(); ++idx)
    sum += digits[idx];

  for (auto it = digits.rbegin(); it != digits.rend(); ++it)
    std::cout << static_cast<size_t>(*it);
  
  std::cout << "\nSum of digits = " << sum << '\n';
}