#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

int main()
{
  std::vector<size_t> prev(1, 1);
  std::vector<size_t> curr(1, 1);

  for (size_t f = 2; f != 10000; ++f)
  {
    std::vector<size_t> copy = curr;

    // Add
    for (size_t idx = 0; idx != prev.size(); ++idx)
      curr[idx] += prev[idx];

    // Manage overflows.
    for (size_t idx = curr.size(); idx != 0; --idx)
    {
      for (size_t digit = idx - 1; curr[digit] >= 10; ++digit)
      {
        if (digit + 1 == curr.size())
          curr.push_back(curr[digit] / 10);
        else
          curr[digit + 1] += curr[digit] / 10;

        curr[digit] %= 10;
      }
    }

    if (curr.size() >= 1000)
    {
      std::cout << f + 1 << '\n';
      break;
    }

    prev = copy;
  }

  std::ostream_iterator<size_t> out_it (std::cout, " ");
  std::copy(curr.rbegin(), curr.rend(), out_it);
  std::cout << '\n';
}