#include "BigInt.h"

#include <iterator>
#include <algorithm>

std::ostream &operator<<(std::ostream &os, BigInt const &rhs)
{
  std::copy(
    rhs.digits.rbegin(), 
    rhs.digits.rend(), 
    std::ostream_iterator<int32_t>(os)
  );

  return os;
}