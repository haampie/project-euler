#include "BigInt.h"

std::pair<BigInt, size_t> BigInt::divide_shift(BigInt const &divisor, size_t decimals) const
{
  BigInt result;
  BigInt window;

  if (*this == 0)
    return {0, 0};

  size_t idx = digits.size();
  size_t shift = 0;

  while (window < divisor)
  {
    window.push_front(idx == 0 ? 0 : digits[idx - 1]);
    ++shift;

    if (idx != 0)
      --idx;
  }

  while(result.size() <= decimals)
  {
    size_t times = 0;

    for (; window >= divisor; ++times)
      window -= divisor;
    
    result.push_front(times);

    if (window == 0 && idx == 0)
      break;

    if (window == 0) {
      if (idx != 0 && digits[idx - 1] != 0)
        window.push_front(digits[idx - 1]);
    } else {
      window.push_front(idx == 0 ? 0 : digits[idx - 1]);
    }
    
    if (idx != 0)
      --idx;
  }

  if (result.size() == decimals + 1)
  {
    if (result.digits[0] >= 5)
      ++result.digits[1];

    result.digits.pop_front();
    result.overflow();
  }

  return {result, shift - divisor.size()};
}