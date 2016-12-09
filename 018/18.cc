#include <iostream>
#include <algorithm>

size_t max(size_t a, size_t b)
{
  return a < b ? b : a;
}

int main()
{
  std::vector<size_t> prev(15, 0);
  std::vector<size_t> curr(15, 0);

  for (size_t y = 0; y != 15; ++y)
  {
    for (size_t x = 0; x <= y; ++x)
    {
      size_t num;
      std::cin >> num;
      curr[x] = num + (x > 0 ? max(prev[x], prev[x - 1]) : prev[x]);
    }

    prev = curr;
  }

  std::cout << *std::max_element(curr.begin(), curr.end()) << '\n';
}