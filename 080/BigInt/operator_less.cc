#include "BigInt.h"

bool BigInt::operator<(BigInt const &rhs) const
{
  if (digits.size() < rhs.digits.size())
    return true;

  if (digits.size() > rhs.digits.size())
    return false;

  for (size_t idx = digits.size(); idx != 0; --idx)
  {
    if (digits[idx - 1] > rhs.digits[idx - 1])
      return false;

    if (digits[idx - 1] < rhs.digits[idx - 1])
      return true;
  }

  return false;
}