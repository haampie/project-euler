#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

int main()
{
  size_t index = 1'000'000 - 1;
  size_t size = 10;

  // Vector containing 0, ..., size - 1.
  std::vector<size_t> items;
  std::vector<size_t> ordered;

  for (size_t idx = 0; idx != size; ++idx)
    items.push_back(idx);

  // Compute factorial(size - 1).
  size_t combinations = 1;
  for (size_t idx = 1; idx <= size; ++idx)
    combinations *= idx;

  for (size_t idx = size; idx != 0; --idx)
  {
    combinations /= idx;
    auto it = items.begin() + (index / combinations);
    index %= combinations;

    // Move to the back.
    std::rotate(it, it + 1, items.end());

    std::ostream_iterator<size_t> out_it (std::cout, " ");
    std::copy ( items.begin(), items.end(), out_it );
    std::cout << '\n';
  }
}