#include <iostream>
#include <algorithm>
#include <iterator>

int main()
{
  std::vector<size_t> curr(100, 0);
  std::vector<size_t> prev(100, 0);
  prev[1] = 1;

  size_t max = 1000;
  for (size_t row = 1; row != 101; ++row)
  {
    for (size_t x = 1; x < max && x <= 1 + row / 2; ++x)
    {
      curr[x] = prev[x - 1] + prev[x];

      if (curr[x] >= 1'000'000)
      {
        std::cout << "(" << row << "," << x - 1 << ")\n";
        max = x;
        continue;
      }
    }

    if (row % 2 == 0)
      curr[1 + row / 2] = 2 * prev[row / 2];




    // std::ostream_iterator<size_t> out(std::cout, ", ");
    // std::copy(curr.begin() + 0, curr.begin() + (max < 2 + row / 2 ? max : 2 + row / 2), out);
    // std::cout << '\n';

    prev = curr;
  }
}