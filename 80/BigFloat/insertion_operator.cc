#include "BigFloat.h"

#include <iterator>
#include <algorithm>

std::ostream &operator<<(std::ostream &os, BigFloat const &rhs)
{
  if (rhs.big_digits.digits.size() == 0)
    return os << "0.0";

  os << *rhs.big_digits.digits.rbegin() << '.';

  std::copy(
    rhs.big_digits.digits.rbegin() + 1, 
    rhs.big_digits.digits.rend(), 
    std::ostream_iterator<int32_t>(os)
  );

  return os << 'e' << (rhs.exponent < 0 ? "" : "+") << rhs.exponent;
}