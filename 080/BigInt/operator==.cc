#include "BigInt.h"

bool BigInt::operator==(size_t rhs) const
{
  if (rhs == 0 && digits.size() == 0)
    return true;

  size_t idx = 0;

  for (; rhs != 0; rhs /= 10, ++idx)
    if (idx == digits.size() || digits[idx] != rhs % 10)
      return false;

  return idx == digits.size();
}