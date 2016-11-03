#include <iostream>
#include <vector>

size_t money_maker(size_t left, std::vector<size_t> const &coins, size_t idx = 0)
{
  if (left == 0)
    return 1;

  if (idx == coins.size())
    return 0;

  size_t total = 0;

  for (size_t next = idx; next != coins.size(); ++next)
    if (left >= coins[next])
      total += money_maker(left - coins[next], coins, next);

  return total;
}

int main()
{
  std::vector<size_t> coins{200, 100, 50, 20, 10, 5, 2, 1};

  // No dynamic programming necessary for N = 200.
  std::cout << money_maker(200, coins) << '\n';
}