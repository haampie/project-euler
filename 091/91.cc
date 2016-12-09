#include <iostream>
#include <algorithm>

size_t gcd(size_t a, size_t b)
{
  if (b == 0)
    return a;

  return gcd(b, a % b);
}

inline size_t in_coordinate(size_t x, size_t y, size_t size)
{
  size_t gcd_xy = gcd(x, y);
  size_t dx = x / gcd_xy;
  size_t dy = y / gcd_xy;
  return 2 * std::min( (size - y) / dx, x / dy);
}

int main()
{
  for (size_t n = 1; n <= 100; ++n)
  {
    // size_t count = 3 * n * n;
    size_t count = 0;

    for (size_t y = 1; y <= n; ++y)
      for (size_t x = 1; x <= n; ++x)
        count += in_coordinate(x, y, n);

    std::cout << count << '\n';
  }
}