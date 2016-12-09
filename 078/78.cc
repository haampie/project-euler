#include <iostream>
#include <vector>

std::vector<size_t> generalized_pentagonal_below(size_t N)
{
  std::vector<size_t> pentagonals;

  size_t next_even = 0;
  size_t next_odd = 0;
  size_t diff_even = 1;
  size_t diff_odd = 2;
  do
  {
    next_even += diff_even;
    diff_even += 3;
    pentagonals.push_back(next_even);
    next_odd += diff_odd;
    diff_odd += 3;
    pentagonals.push_back(next_odd);
  } while (pentagonals.back() < N);

  return pentagonals;
}

int main()
{
  size_t N = 100'000;
  
  auto pentagonals = generalized_pentagonal_below(N);

  std::vector<int32_t> partitionings(N, 0);
  partitionings[0] = 1;

  for (size_t p = 0; p != N; ++p)
  {
    for (size_t idx = 0; pentagonals[idx] <= p; ++idx)
      if (idx % 4 < 2)
        partitionings[p] += partitionings[p - pentagonals[idx]];
      else
        partitionings[p] -= partitionings[p - pentagonals[idx]];

    partitionings[p] %= 1'000'000;

    if (partitionings[p] == 0)
    {
      std::cout << p << '\n';
      break;
    }
  }
}