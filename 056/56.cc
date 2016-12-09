#include <iostream>
#include <vector>
#include <cmath>

class Biggy {
  std::vector<uint16_t> digits;

  inline void overflow()
  {
    for (size_t idx = 0; idx != digits.size(); ++idx)
    {
      uint16_t times = digits[idx] / 10;
      if (times != 0)
      {
        digits[idx] %= 10;
        if (idx + 1 == digits.size())
          digits.push_back(times);
        else
          digits[idx + 1] += times;
      }
    }
  }

public:

  Biggy(size_t num)
  {
    for (; num != 0; num /= 10)
      digits.push_back(num % 10);
  }

  Biggy &operator*=(uint16_t num)
  {
    for (size_t idx = 0; idx != digits.size(); ++idx)
      digits[idx] *= num;

    overflow();

    return *this;
  }

  size_t digits_sum() const
  {
    size_t sum = 0;

    for (size_t idx = 0; idx != digits.size(); ++idx)
      sum += digits[idx];

    return sum;
  }
};

size_t digits_sum(size_t a, size_t b)
{
  Biggy biggy(1);

  for (size_t idx = 0; idx != b; ++idx)
    biggy *= a;

  return biggy.digits_sum();
}

int main()
{
  std::vector<double> logs{0.0};

  for (size_t num = 1; num != 100; ++num)
    logs.push_back(std::log10(static_cast<double>(num)));

  size_t max_sum = 0;

  for (size_t a = 99; a != 0; --a)
  {
    if (std::floor(1 + 99 * logs[a]) * 9 < max_sum)
      break;

    for (size_t b = 99; b != 0; --b)
    {
      if (std::floor(1 + b * logs[a]) * 9 < max_sum)
        break;

      size_t current_sum = digits_sum(a, b);

      if (current_sum > max_sum)
        max_sum = current_sum;
    }
  }

  std::cout << max_sum << '\n';
}