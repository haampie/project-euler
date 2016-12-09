#include <iostream>

struct Frac
{
  size_t num;
  size_t den;

  Frac(size_t num, size_t den)
    : num(num), den(den)
  {}
};

int main()
{
  Frac best{0, 1};

  for (size_t den = 2; den <= 1'000'000; ++den)
  {
    size_t num = (3 * den - 1) / 7;

    if (num * best.den > den * best.num)
      best = {num, den};
  }

  std::cout << best.num << '/' << best.den << '\n';
}