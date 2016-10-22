#include <iostream>
#include <vector>

class SmallBigNum {
  std::vector<size_t> d_digits;

  friend std::ostream &operator<<(std::ostream &out, SmallBigNum const &num);

public:
  SmallBigNum()
    : d_digits(1, 1)
  {}

  SmallBigNum &operator*=(size_t num)
  {
    // Multiply all factors with num.
    for (size_t idx = 0; idx != d_digits.size(); ++idx)
      d_digits[idx] *= num;

    // Move the carry over.
    for (size_t idx = d_digits.size(); idx > 0; --idx)
    {
      for (size_t digit = idx - 1; d_digits[digit] >= 10; ++digit)
      {
        // Make some more space.
        if (digit + 1 == d_digits.size()) {
          d_digits.push_back(d_digits[digit] / 10);
        } else {
          d_digits[digit + 1] += d_digits[digit] / 10;
        }
        d_digits[digit] %= 10;
      }
    }

    return *this;
  }

  size_t sumOfDigits()
  {
    size_t sum = 0;
    for (auto digit : d_digits)
      sum += digit;

    return sum;
  }
};

std::ostream &operator<<(std::ostream &out, SmallBigNum const &num)
{
  for (auto it = num.d_digits.rbegin(); it != num.d_digits.rend(); ++it)
    std::cout << *it;

  return out;
}

int main()
{
  SmallBigNum num;

  for (size_t multiplier = 2; multiplier != 101; ++multiplier)
  {
    num *= multiplier;
    std::cout << num << '\n';
  }

  std::cout << num.sumOfDigits() << '\n';
}