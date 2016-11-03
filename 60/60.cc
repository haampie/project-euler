#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <string>
#include <iterator>
#include <map>

typedef std::tuple<
  std::vector<size_t>, 
  std::vector<size_t>, 
  std::vector<size_t>
> groups;

typedef std::pair<size_t, size_t> duo;

inline bool first_group(size_t const p)
{
  size_t const rem = p % 30;
  return rem == 1 || rem == 7 || rem == 13 || rem == 19; 
}

groups primes_modulo_30_groups(size_t N)
{
  std::vector<bool> prime(N, true);

  for (size_t x = 3; x * x <= N; x += 2)
    if (prime[x])
      for (size_t m = x * x; m < N; m += 2 * x)
        prime[m] = false;

  groups primes{
    {3, 7, 11, 13, 17, 19, 23, 29},
    {3, 7, 11, 13, 17, 19, 23, 29},
    {2, 3, 5, 7, 11, 13, 17, 19, 23, 29}
  };

  for (size_t x = 31; x < N; x += 2)
    if (prime[x])
    {
      std::get<2>(primes).push_back(x);
      if (first_group(x))
        std::get<0>(primes).push_back(x);
      else
        std::get<1>(primes).push_back(x);
    }

  return primes;
}

bool is_prime(size_t const num, std::vector<size_t> const &test)
{
  for (size_t idx = 0; idx != test.size() && test[idx] * test[idx] <= num; ++idx)
    if (num % test[idx] == 0)
      return false;

  return true;
}

inline bool is_concat_prime(size_t p1, size_t p2, std::vector<size_t> const &test, std::map<duo, bool> &cache)
{
  if (cache.count(std::make_pair(p1, p2)))
    return cache[std::make_pair(p1, p2)];

  auto fst = std::to_string(p1) + std::to_string(p2);
  auto snd = std::to_string(p2) + std::to_string(p1);

  bool res = is_prime(stoul(fst), test) && is_prime(stoul(snd), test);

  cache.insert(std::make_pair(std::make_pair(p1, p2), res));

  return res;
}

size_t search(std::vector<size_t> const &group, std::vector<size_t> const &test, size_t cap)
{
  std::map<duo, bool> cache;

  for (size_t a = 0; a != group.size() - 4; ++a)
  {
    if (5 * group[a] > cap) break;
    for (size_t b = a + 1; b != group.size() - 3; ++b)
    {
      if (group[a] + 4 * group[b] > cap) break;
      if (!is_concat_prime(group[a], group[b], test, cache))
        continue;

      for (size_t c = b + 1; c != group.size() - 2; ++c)
      {
        if (group[a] + group[b] + 3 * group[b] > cap) break;
        if (!is_concat_prime(group[b], group[c], test, cache) || 
          !is_concat_prime(group[a], group[c], test, cache))
          continue;

        for (size_t d = c + 1; d != group.size() - 1; ++d)
        {
          if (group[a] + group[b] + group[c] + 2 * group[d] > cap) break;
          if (!is_concat_prime(group[c], group[d], test, cache) || 
            !is_concat_prime(group[b], group[d], test, cache) ||
            !is_concat_prime(group[a], group[d], test, cache))
            continue;

          for (size_t e = d + 1; e != group.size(); ++e)
          {
            if (group[a] + group[b] + group[c] + group[d] + group[e] > cap) break;
            if (!is_concat_prime(group[d], group[e], test, cache) || 
              !is_concat_prime(group[c], group[e], test, cache) ||
              !is_concat_prime(group[b], group[e], test, cache) ||
              !is_concat_prime(group[a], group[e], test, cache))
              continue;

            cap = group[a] + group[b] + group[c] + group[d] + group[e];

            std::cout << group[a] << ' ' << group[b] << ' '  
                      << group[c] << ' ' << group[d] << ' ' 
                      << group[e] << '\n';
          }
        }
      }
    }
  }

  return cap;
}

int main()
{
  auto const primes = primes_modulo_30_groups(10'000);
  auto const all = std::get<2>(primes);

  size_t sum = 30'000 * 5;

  sum = search(std::get<0>(primes), all, sum);
  sum = search(std::get<1>(primes), all, sum);
}