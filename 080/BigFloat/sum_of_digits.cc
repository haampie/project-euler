#include "BigFloat.h"

size_t BigFloat::sum_of_digits(size_t digits) const
{
  size_t sum = 0;

  for (size_t idx = big_digits.digits.size(); idx > 0 && idx + digits > big_digits.digits.size(); --idx)
    sum += big_digits.digits[idx - 1];

  return sum;
}