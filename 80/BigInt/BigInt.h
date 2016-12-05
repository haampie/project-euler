#ifndef INCLUDE_BIG_INT
#define INCLUDE_BIG_INT

#include <iostream>
#include <deque>
#include <tuple>

class BigFloat;

class BigInt {
  friend class BigFloat;
  friend std::ostream &operator<<(std::ostream &os, BigInt const &rhs);
  friend std::ostream &operator<<(std::ostream &os, BigFloat const &rhs);
  std::deque<int32_t> digits;
  size_t shifted = 0;

public:
  BigInt() = default;
  
  BigInt(std::deque<int32_t> digits);

  BigInt(size_t num);

  BigInt &operator-=(BigInt const &rhs);

  bool operator<(BigInt const &rhs) const;

  BigInt divide(BigInt const &divisor, size_t decimals) const;

  std::pair<BigInt, size_t> divide_shift(BigInt const &divisor, size_t decimals) const;

  bool operator==(size_t rhs) const;

  inline bool operator>=(BigInt const &rhs) const
  {
    return !(*this < rhs);
  }

  inline bool operator!=(size_t rhs) const
  {
    return !(*this == rhs);
  }

  inline void push_front(int32_t num)
  {
    digits.push_front(num);
  }

  inline int32_t operator[](size_t idx) const
  {
    return digits[idx];
  }

  inline size_t size() const
  {
    return digits.size();
  }

private:
  inline void overflow()
  {
    for (size_t idx = 0; idx != digits.size(); ++idx)
    {
      if (digits[idx] >= 10)
      {
        if (idx + 1 == digits.size())
          digits.push_back(digits[idx] / 10);
        else
          digits[idx + 1] += digits[idx] / 10;
        digits[idx] %= 10;
      }
    }
  }

  inline void underflow()
  {
    for (size_t idx = 0; idx + 1 != digits.size(); ++idx)
      while (digits[idx] < 0)
      {
        digits[idx] += 10;
        --digits[idx + 1];
      }
  }

  inline void remove_zeros()
  {
    while(digits.size() > 0 && digits.front() == 0)
      digits.pop_front();
  }
};

#endif