#include "BigFloat.h"

bool BigFloat::operator<(BigFloat const &rhs) const
{
  if (exponent < rhs.exponent)
    return true;

  if (exponent > rhs.exponent)
    return false;

  return big_digits < rhs.big_digits;
}