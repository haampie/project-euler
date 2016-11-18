#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

std::vector<size_t> expansion_of_square_root(size_t square)
{
  size_t integer_part = 1;

  for (; integer_part * integer_part + 2 * integer_part < square; ++integer_part);

  if (integer_part * integer_part == square)
    return {};

  std::vector<size_t> expansion;
  expansion.push_back(integer_part);

  size_t m = 0;
  size_t d = 1;

  for (size_t idx = 0; expansion[idx] != 2 * expansion[0]; ++idx)
  {
    m = d * expansion[idx] - m;
    d = (square - m * m) / d;
    expansion.push_back((integer_part + m) / d);
  }

  return expansion;
}

int main()
{
  size_t count = 0;
  for(size_t idx = 1; idx <= 10'000; ++idx)
  {
    auto const expansion = expansion_of_square_root(idx);

    if (expansion.size() == 0 || expansion.size() % 2 == 1)
      continue;

    ++count;

    std::cout << idx << ": " << expansion.size() << '\n';

    // std::copy(
    //   expansion.begin(),
    //   expansion.end(),
    //   std::ostream_iterator<size_t>(std::cout, " ")
    // );

    // std::cout << '\n';
  }

  std::cout << "total = " << count << '\n';
}