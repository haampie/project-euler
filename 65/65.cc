#include <iostream>
#include <iterator>
#include <algorithm>

class Biggy {
  friend std::ostream &operator<<(std::ostream &os, Biggy const &biggy);

  std::vector<size_t> digits;

  inline void overflow()
  {
    for (size_t idx = 0; idx != digits.size(); ++idx)
    {
      size_t times = digits[idx] / 10;
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
    for(size_t idx = 0; idx != rhs.digits.size(); ++idx)
    {
      if (idx == digits.size())
        digits.push_back(rhs.digits[idx]);
      else
        digits[idx] += rhs.digits[idx];
    }

    overflow();
    
    return *this;
  }

  Biggy &operator*=(size_t num)
  {
    for(size_t idx = 0; idx != digits.size(); ++idx)
      digits[idx] *= num;

    overflow();

    return *this;
  }

  inline size_t sum_digits() const
  {
    size_t sum = 0;
    for (size_t idx = 0; idx != digits.size(); ++idx)
      sum += digits[idx];

    return sum;
  }
};

std::ostream &operator<<(std::ostream &os, Biggy const &biggy)
{
  std::copy(biggy.digits.rbegin(), biggy.digits.rend(), std::ostream_iterator<size_t>(os, ""));
  return os;
}

int main()
{
  Biggy prev_n(2);
  Biggy curr_n(3);

  Biggy curr_d(1);
  Biggy prev_d(1);

  for (size_t idx = 0; idx < 98; ++idx)
  {
    size_t a_n = (idx % 3 == 0 ? 2 * (idx / 3 + 1) : 1);

    Biggy new_n(curr_n);
    Biggy new_d(curr_d);
    
    new_n *= a_n;
    new_n += prev_n;

    new_d *= a_n;
    new_d += prev_d;

    std::cout << (3 + idx) << ": " << new_n << '/' << new_d << '\n';

    prev_n = curr_n;
    curr_n = new_n;
    prev_d = curr_d;
    curr_d = new_d;
  }

  std::cout << "Sum digits numerator = " << curr_n.sum_digits() << '\n';
}