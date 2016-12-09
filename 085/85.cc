#include <iostream>
#include <cstdlib>
#include <tuple>

inline size_t rectangles(size_t x, size_t y)
{
  return x * (x + 1) * y * (y + 1) / 4;
}

int main()
{
  int64_t const max = 2'000'000;
  size_t dist = max;
  std::pair<size_t, size_t> coord{0,0};

  for (size_t y = 1; rectangles(1, y - 1) <= max; ++y)
  {
    for (size_t x = 1; x <= y && rectangles(x - 1, y) <= max; ++x)
    {
      size_t num = rectangles(x, y);
      size_t candidate = std::abs(max - static_cast<int64_t>(num));

      if (candidate < dist)
      {
        dist = candidate;
        coord = std::make_pair(x, y);
      }
    }
  }

  std::cout << dist << " via "
            << coord.first << 'x' << coord.second 
            << " = " << coord.first * coord.second
            << '\n';
}