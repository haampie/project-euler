#include <iostream>
#include <algorithm>
#include <iterator>

class Biggy {
  friend std::ostream &operator<<(std::ostream &os, Biggy const &biggy);

  std::vector<uint8_t> digits;

  inline void overflow()
  {
    for (size_t idx = 0; idx != digits.size(); ++idx)
    {
      uint8_t times = digits[idx] / 10;
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

  Biggy &add_reverse()
  {
    for (size_t left = 0, right = digits.size() - 1; left <= right; ++left, --right)
      digits[left] = digits[right] = digits[left] + digits[right];

    overflow();

    return *this;
  }

  bool is_palindrome() const
  {
    for (size_t left = 0, right = digits.size() - 1; left < right; ++left, --right)
      if (digits[left] != digits[right])
        return false;

    return true;
  }
};

std::ostream &operator<<(std::ostream &os, Biggy const &biggy)
{
  std::copy(biggy.digits.rbegin(), biggy.digits.rend(), std::ostream_iterator<size_t>(os, ""));
  return os;
}

bool is_lychrel(size_t num)
{
  Biggy biggy(num);

  biggy.add_reverse();

  for (size_t idx = 1; idx != 50; ++idx, biggy.add_reverse())
    if (biggy.is_palindrome())
      return false;

  return true;
}

int main()
{
  size_t count = 0;
  for (size_t idx = 10; idx != 10'000; ++idx)
  {
    if (is_lychrel(idx))
    {
      std::cout << idx << '\n';
      ++count;
    }
  }

  std::cout << count << '\n';
}