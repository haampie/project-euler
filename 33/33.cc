#include <iostream>

size_t gcd(size_t a, size_t b)
{
  if (b > a)
    return gcd(b, a);

  if (b == 0)
    return a;

  return gcd(b, a % b);
}

bool equals(size_t a, size_t b, size_t c, size_t d)
{
  size_t gcd1 = gcd(a, b);
  size_t gcd2 = gcd(c, d);

  return a / gcd1 == c / gcd2 && b / gcd1 == d / gcd2;
}

int main()
{
  for (size_t num = 11; num != 100; ++num)
  {
    if (num % 10 == 0)
      continue;

    size_t num1 = num / 10;
    size_t num2 = num % 10;

    for (size_t den = num + 1; den != 100; ++den)
    {
      if (den % 10 == 0)
        continue;

      size_t den1 = den / 10;
      size_t den2 = den % 10;

      if (num1 == den1 && equals(num2, den2, num, den)) {
        std::cout << num << ' ' << den << '\n';
      }

      if (num2 == den1 && equals(num1, den2, num, den)) {
        std::cout << num << ' ' << den << '\n';
      }

      if (num1 == den2 && equals(num2, den1, num, den)) {
        std::cout << num << ' ' << den << '\n';
      }

      if (num2 == den2 && equals(num1, den1, num, den)) {
        std::cout << num << ' ' << den << '\n';
      }
    }
  }
}