#include <iostream>
#include <array>
#include <algorithm>
#include <iterator>

template <class T, size_t N>
class FixedDigits
{
  template<class U, size_t M>
  friend std::ostream &operator<<(std::ostream &os, FixedDigits<U, M> rhs);
  
  std::array<T, N> digits;

public:
  FixedDigits()
  {
    digits.fill(0);
  }

  FixedDigits(size_t num)
  {
    digits.fill(0);
    for (size_t idx = 0; num != 0 && idx < N; ++idx)
    {
      digits[idx] = num % 10;
      num /= 10;
    }
  }

  FixedDigits &operator*=(FixedDigits const &rhs)
  {
    return *this = (*this) * rhs;
  }

  FixedDigits operator*(FixedDigits const &rhs) const
  {
    FixedDigits product;

    // Product
    for (size_t idx = 0; idx < N; ++idx)
      for (size_t l = 0; l <= idx; ++l)
        product.digits[idx] += digits[l] * rhs.digits[idx - l];

    // Overflow
    for (size_t idx = 0; idx < N; ++idx)
    {
      if (product.digits[idx] > 10)
      {
        T carry = product.digits[idx] / 10;
        product.digits[idx] %= 10;

        if (idx + 1 < N)
          product.digits[idx + 1] += carry;
      }
    }

    return product;
  }
};

template<class T, size_t N>
std::ostream &operator<<(std::ostream &os, FixedDigits<T, N> rhs)
{
  std::copy(rhs.digits.rbegin(), rhs.digits.rend(), std::ostream_iterator<size_t>(os));
  return os;
}

template<class T, size_t N>
FixedDigits<T, N> mod_N(FixedDigits<T, N> prod, FixedDigits<T, N> base, size_t power)
{
  while (power != 1)
  {
    if (power % 2 != 0)
    {
      prod *= base;
      --power;
      continue;
    }

    base *= base;
    power /= 2;
  }

  return prod * base;
}

int main()
{
  FixedDigits<size_t, 10000> prod(28433);
  FixedDigits<size_t, 10000> base(2);

  auto digits = mod_N(prod, base, 7830457);
  
  std::cout << digits << '\n';
}