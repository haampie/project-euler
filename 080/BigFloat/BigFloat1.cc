#include "BigFloat.h"

BigFloat::BigFloat(BigInt big_digits, size_t exponent, size_t precision)
  : big_digits(big_digits), 
    exponent(exponent),
    precision(precision)
{}