#include <iostream>
#include <vector>
#include <algorithm>

bool three_or_more_equal(size_t p)
{
  // Skip this first digit.
  p /= 10;

  char count[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

  while (p != 0)
  {
    size_t digit = p % 10;
    ++count[digit];
    p /= 10;
  }

  for (size_t idx = 0; idx != 10; ++idx)
    if (count[idx] >= 3)
      return true;

  return false;
}

std::vector<size_t> primes_below_with_equal_digits(size_t N)
{
  std::vector<bool> prime(N, true);

  for (size_t x = 3; x * x <= N; x += 2)
    if (prime[x])
      for (size_t m = x * x; m < N; m += 2 * x)
        prime[m] = false;

  std::vector<size_t> primes;

  primes.push_back(2);

  for (size_t x = 3; x < N; x += 2)
    if (prime[x] && three_or_more_equal(x))
      primes.push_back(x);

  return primes;
}

bool is_starting_point(size_t p)
{
  // Skip this first digit.
  p /= 10;

  char count[3] = {0, 0, 0};

  while (p != 0)
  {
    size_t digit = p % 10;
    if (digit < 3) ++count[digit];
    p /= 10;
  }

  return count[0] >= 3 || count[1] >= 3 || count[2] >= 3;
}

std::vector<size_t> find(size_t p, size_t digit)
{
  std::vector<size_t> position;

  size_t point = 10;
  p /= 10;

  while (p != 0)
  {
    if (p % 10 == digit)
      position.push_back(point);
    p /= 10;
    point *= 10;
  }

  std::vector<size_t> possibilities;

  for (size_t fst = 0; fst < position.size(); ++fst)
    for (size_t snd = fst + 1; snd < position.size(); ++snd)
      for (size_t trd = snd + 1; trd < position.size(); ++trd)
        possibilities.push_back(position[fst] + position[snd] + position[trd]);

  return possibilities;
}

int main()
{
  auto primes = primes_below_with_equal_digits(10'000'000);
  
  // Loop over subset of primes.
  for (auto p : primes)
  {
    // Check if it has at least 3 zeros, ones or twos
    if (!is_starting_point(p))
      continue;

    // If so, loop over them.
    for (size_t start = 0; start != 3; ++start)
    {
      
      for (auto combi : find(p, start))
      {
        size_t count = 1;

        for (size_t idx = 1; idx != 10; ++idx)
          if (std::binary_search(primes.begin(), primes.end(), p + idx * combi))
            ++count;

        if (count >= 8)
        {
          std::cout << p << " with " << combi << '\n';

          for (size_t idx = start; idx != 10; ++idx)
            if (std::binary_search(primes.begin(), primes.end(), p + idx * combi))
              std::cout << p + idx * combi << ' ';

          std::cout << '\n';

          // return 0;
        }
      }
    }
  }
}