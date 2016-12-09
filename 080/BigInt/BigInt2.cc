#include "BigInt.h"

BigInt::BigInt(size_t num)
{
  for (; num != 0; num /= 10)
    digits.push_back(num % 10);
}