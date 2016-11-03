#include <iostream>
#include <vector>

bool unique(std::vector<bool> digits, size_t num)
{
  while (num != 0) {
    if (digits[num % 10])
      return false;

    digits[num % 10] = true;
    
    num /= 10;
  }

  return true;
}

int main()
{
  for (size_t a = 1; a != 10; ++a)
  {
    for (size_t b = 1; b != 10; ++b)
    {
      if (a == b)
        continue;

      for (size_t c = 1; c != 10; ++c)
      {
        if (c == a || c == b)
          continue;

        for (size_t d = 1; d != 10; ++d)
        {
          if (d == a || d == b || d == c)
            continue;

          for (size_t e = 1; e != 10; ++e)
          {
            if (e == a || e == b || e == c || e == d)
              continue;

            std::vector<bool> digits{true, false, false, false, 
              false, false, false, false, false, false};

            digits[a] = digits[b] = digits[c] = digits[d] = digits[e] = true;

            {
              size_t lhs = 10 * a + b;
              size_t rhs = 100 * c + 10 * d + e;

              if (lhs * rhs < 10000 && unique(digits, lhs * rhs))
                std::cout << lhs << '*' << rhs << " = " << lhs * rhs << '\n';
            }

            {
              size_t lhs = a;
              size_t rhs = 1000 * b + 100 * c + 10 * d + e;

              if (lhs * rhs < 10000 && unique(digits, lhs * rhs))
                std::cout << lhs << '*' << rhs << " = " << lhs * rhs << '\n';
            }
          }
        }
      }
    }
  }
}