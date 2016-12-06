#include <iostream>
#include <array>
#include <algorithm>
#include <iterator>

using ten_digits = std::array<uint16_t, 10>;

ten_digits to_ten_digits(size_t num)
{
  ten_digits ten;
  ten.fill(0);
  for (size_t idx = 0; num != 0; ++idx)
  {
    ten[idx] = num % 10;
    num /= 10;
  }
  return ten;
}

ten_digits prod_10_digits(ten_digits const &lhs, ten_digits const &rhs)
{
  ten_digits product;
  product.fill(0);

  for (size_t idx = 0; idx < 10; ++idx)
    for (size_t l = 0; l <= idx; ++l)
      product[idx] += lhs[l] * rhs[idx - l];

  for (size_t idx = 0; idx < 10; ++idx)
  {
    if (product[idx] > 10)
    {
      uint16_t carry = product[idx] / 10;
      product[idx] %= 10;

      if (idx + 1 < 10)
        product[idx + 1] += carry;
    }
  }

  return product;
}

ten_digits mod_10_to_the_10(ten_digits prod, ten_digits base, size_t power)
{
  while (power != 1)
  {
    if (power % 2 != 0)
    {
      prod = prod_10_digits(prod, base);
      --power;
      continue;
    }

    base = prod_10_digits(base, base);
    power /= 2;
  }

  return prod_10_digits(prod, base);
}

int main()
{
  auto digits = mod_10_to_the_10(to_ten_digits(28433), to_ten_digits(2), 7830457);
  std::copy(digits.rbegin(), digits.rend(), std::ostream_iterator<size_t>(std::cout));
  std::cout << '\n';
}