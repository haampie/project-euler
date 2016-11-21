#include <iostream>

struct Frac {
  size_t num;
  size_t den;
  Frac(size_t num, size_t den)
    : num(num), den(den)
  {}
};

size_t count(Frac lhs, Frac rhs)
{
  Frac mid{lhs.num + rhs.num, lhs.den + rhs.den};

  if (mid.den > 12000)
    return 0;

  size_t sum = 1;
  sum += count(lhs, mid);
  sum += count(mid, rhs);
  return sum;
}

int main()
{
  std::cout << count({1, 3}, {1, 2}) << '\n';
}