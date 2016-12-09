#include "BigFloat.h"

#include <tuple>
#include <algorithm>

BigFloat BigFloat::operator/(BigFloat const &rhs) const
{
  size_t new_precision = std::max(precision, rhs.precision);
  auto result = big_digits.divide_shift(rhs.big_digits, new_precision);
  return BigFloat(std::get<0>(result), exponent - rhs.exponent - std::get<1>(result), new_precision);
}