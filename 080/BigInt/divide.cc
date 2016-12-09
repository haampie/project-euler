#include "BigInt.h"

BigInt BigInt::divide(BigInt const &divisor, size_t decimals) const
{
  return std::get<0>(divide_shift(divisor, decimals));
}