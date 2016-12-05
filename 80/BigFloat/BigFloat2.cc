#include "BigFloat.h"

BigFloat::BigFloat(size_t num, size_t precision)
  : big_digits(num), 
    exponent(0),
    precision(precision)
{
  for (; num != 0; num /= 10)
    ++exponent;

  --exponent;
}