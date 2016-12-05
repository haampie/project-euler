#include "BigFloat/BigFloat.h"
#include "BigInt/BigInt.h"

#include <tuple>

int main()
{
  BigFloat x(BigInt(1), 0, 130);
  BigFloat twee(BigInt(2), 0, 1);

  size_t sum = 0;

  for (size_t square = 2; square < 100; ++square)
  {
    if (square == 4 || square == 9 || square == 16 || square == 25
      || square == 36 || square == 49 || square == 64 || square == 81)
      continue;

    BigFloat s(square, 3);

    for (size_t idx = 0; idx != 10; ++idx)
      x = (x + (s / x)) / twee;

    std::cout << x << '\n' << x.sum_of_digits(100) << '\n';
    
    sum += x.sum_of_digits(100);
  }

  std::cout << sum << '\n';
}