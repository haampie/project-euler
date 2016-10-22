#include <iostream>

int main()
{
  for (size_t a = 1; a <= 1000 / 3; ++a)
  {
    for (size_t b = a; b <= (1000 - a) / 2; ++b)
    {
      size_t c = 1000 - a - b;

      if ( a * a + b * b == c * c) {
        std::cout << '(' << a << ',' << b << ',' << c << ")\n";
      }

      if ( a * a + c * c == b * b) {
        std::cout << '(' << a << ',' << b << ',' << c << ")\n";
      }

      if ( b * b + c * c == a * a) {
        std::cout << '(' << a << ',' << b << ',' << c << ")\n";
      }
    }
  }
}