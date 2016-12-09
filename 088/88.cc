#include <iostream>
#include <vector>
#include <set>
#include <numeric>
#include <algorithm>

void products(size_t product, size_t sum, size_t min, std::vector<size_t> &minimal)
{
  size_t const idx = product - sum;

  if (idx >= minimal.size())
    return;

  if (minimal[idx] == 0 || minimal[idx] > product)
    minimal[idx] = product;

  for (size_t num = min; product * num < minimal.size() + sum; ++num)
    products(product * num, sum + num - 1, min, minimal);
}

int main()
{
  size_t const max = 12'000;

  std::vector<size_t> minimal(max + 1, 0);

  products(1, 0, 2, minimal);

  std::set<size_t> unique(minimal.begin() + 2, minimal.end());

  std::cout << std::accumulate(unique.begin(), unique.end(), 0u) << '\n';
}