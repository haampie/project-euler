#include "BigFloat.h"

BigFloat BigFloat::operator+(BigFloat const &rhs) const
{
  // make sure *this is larger.
  if (*this < rhs)
    return rhs + *this;

  BigFloat copy(*this);

  for (int64_t idx = big_digits.digits.size() - 1;; --idx)
  {
    int64_t rhs_idx = idx + exponent - rhs.exponent + rhs.big_digits.digits.size() - big_digits.digits.size();

    if (big_digits.digits.size() - idx > 1 + precision || rhs_idx < 0)
      break;

    if (idx < 0)
    {
      if (rhs_idx < rhs.big_digits.digits.size())
        copy.big_digits.digits.push_front(rhs.big_digits.digits[rhs_idx]);
      else
        copy.big_digits.digits.push_front(0);
    } else {
      if (rhs_idx < rhs.big_digits.digits.size())
        copy.big_digits.digits[idx] += rhs.big_digits.digits[rhs_idx];
    }
  }

  if (copy.big_digits.digits.size() > precision) {
    if (copy.big_digits.digits[0] >= 5)
      ++copy.big_digits.digits[1];

    copy.big_digits.digits.pop_front();
  }

  // Fix overflow.
  for (size_t idx = 0; idx != copy.big_digits.digits.size(); ++idx)
  {
    if (copy.big_digits.digits[idx] >= 10)
    {
      if (idx + 1 == copy.big_digits.digits.size())
      {
        copy.big_digits.digits.push_back(copy.big_digits.digits[idx] / 10);
        ++copy.exponent;
      }
      else
      {
        copy.big_digits.digits[idx + 1] += copy.big_digits.digits[idx] / 10;
      }
      copy.big_digits.digits[idx] %= 10;
    }
  }
  
  while (copy.big_digits.digits.size() > 0 && copy.big_digits.digits.front() == 0)
    copy.big_digits.digits.pop_front();

  return copy;
}