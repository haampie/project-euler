#include <iostream>
#include <algorithm>
#include <iterator>

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

  Biggy &operator+=(Biggy const &rhs)
  {
    for (size_t idx = 0; idx != rhs.digits.size(); ++idx)
      if (idx == digits.size())
        digits.push_back(rhs.digits[idx]);
      else
        digits[idx] += rhs.digits[idx];

    overflow();

    return *this;
  }

  inline size_t digit_count() const
  {
    return digits.size();
  }
};

int main()
{
  size_t times = 0;
  Biggy num(1);
  Biggy den(1);

  for (size_t idx = 0; idx != 1'000; ++idx)
  {
    Biggy tmp = num;
    num += den;
    num += den;
    den += tmp;

    if (num.digit_count() > den.digit_count())
      ++times;
  }

  std::cout << times << '\n';
}