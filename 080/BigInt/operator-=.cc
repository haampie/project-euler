#include "BigInt.h"

BigInt &BigInt::operator-=(BigInt const &rhs)
{
  for (size_t idx = 0; idx != rhs.digits.size(); ++idx)
    if (idx == digits.size())
      digits.push_back(-rhs.digits[idx]);
    else
      digits[idx] -= rhs.digits[idx];

  underflow();

  while (digits.size() > 0 && digits.back() == 0)
    digits.pop_back();

  return *this;
}