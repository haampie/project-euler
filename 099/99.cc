#include <iostream>
#include <cmath>

int main()
{
  size_t max_idx;
  size_t max_base = 1;
  size_t max_exp = 1;
  double max_val = 1;
  for (size_t i = 1; std::cin.good(); ++i)
  {
    size_t base, exp;
    std::cin >> base >> exp;

    double res = exp * log(static_cast<double>(base));

    if (res > max_val)
    {
      max_idx = i;
      max_base = base;
      max_exp = exp;
      max_val = res;
    }
  }

  std::cout << max_idx << ": " << max_base << '^' << max_exp << '\n';
}