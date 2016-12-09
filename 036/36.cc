#include <iostream>
#include <bitset>
#include <vector>

bool palindrome(size_t N)
{
  size_t num = N;
  size_t rev = 0;

  while (num > 0)
  {
    rev = rev * 10 + num % 10;
    num /= 10;
  }

  return rev == N;
}

int main()
{
  for (size_t i = 1; i <= 1024; i += 2)
  {
    size_t copy = i;
    size_t flip = 0;
    size_t length = 0;

    while (copy != 0) {
      flip <<= 1;
      flip |= copy & 1;
      copy >>= 1;
      ++length;
    }

    for (size_t l = 0; l <= 7; ++l)
    {
      size_t a = (flip << (length + 2 * l)) | i;
      size_t b = (flip << (length + 2 * l + 1)) | i | (1 << (length + l));
      size_t c = (flip << (length + 2 * l + 1)) | i;

      if (a < 1'000'000 && palindrome(a)) {
        // std::cout << std::bitset<32>(a) << '\n';
        std::cout << a << '\n';
      }
      if (b < 1'000'000 && palindrome(b)) {
        // std::cout << std::bitset<32>(b) << '\n';
        std::cout << b << '\n';
      }
      if (c < 1'000'000 && palindrome(c)) {
        // std::cout << std::bitset<32>(c) << '\n';
        std::cout << c << '\n';
      }
      // std::cout << a << ' ' << b << ' ' << c << '\n';
    }
  }
}