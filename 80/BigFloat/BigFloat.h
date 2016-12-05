#ifndef INCLUDE_BIG_FLOAT
#define INCLUDE_BIG_FLOAT

#include "../BigInt/BigInt.h"
#include <iostream>

class BigFloat {
  friend std::ostream &operator<<(std::ostream &os, BigFloat const &rhs);

  BigInt big_digits;
  int16_t exponent;
  size_t precision;

public:
  BigFloat(BigInt big_digits, size_t exponent, size_t precision);
  BigFloat(size_t num, size_t precision);

  BigFloat operator/(BigFloat const &rhs) const;
  BigFloat operator+(BigFloat const &rhs) const;
  bool operator<(BigFloat const &rhs) const;

  size_t sum_of_digits(size_t digits) const;
};

#endif