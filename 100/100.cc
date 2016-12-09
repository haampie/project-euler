#include <iostream>

/**
 * General idea:
 * b(b-1) / n(n-1) = 1/2
 * (2n-1)^2 - 2(2b - 1)^2 = -1
 * u = 2n - 1, v = 2b - 1: u^2 - 2v^2 = -1
 * Fundamental solution: (u, v) = (7, 5).
 * Next solutions (u_n, v_n) = (u + v sqrt(2))^(2n + 1).
 * Simplifications lead to what is below.
 */
int main()
{
  size_t b = 3;
  size_t n = 4;
  size_t target = 1'000'000'000'000;

  while (n < target)
  {
    std::cout << '(' << b << ',' << n << ")\n";

    size_t btemp = 3 * b + 2 * n - 2;
    n = 4 * b + 3 * n - 3;
    b = btemp;
  }

  std::cout << '(' << b << ',' << n << ")\n";
}