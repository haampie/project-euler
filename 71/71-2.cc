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
  Frac lhs{2, 5};
  Frac rhs{3, 7};

  while(lhs.den < 1'000'000)
  {
    lhs = {lhs.num + rhs.num, lhs.den + rhs.den};
    std::cout << lhs.num << '/' << lhs.den << '\n';
  }
}