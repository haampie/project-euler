#include <iostream>
#include <vector>
#include <tuple>
#include <functional>
#include <iomanip>

struct StartPoint {
  std::vector<std::vector<char>> to;

  StartPoint()
  : to(6)
  {}
};

std::function<int (int)> figurate(size_t idx) {
  switch (idx) {
    case 0:
      return [](size_t n) { return n * (n + 1) / 2; };
    case 1:
      return [](size_t n) { return n * n; };
    case 2:
      return [](size_t n) { return n * (3 * n - 1) / 2; };
    case 3:
      return [](size_t n) { return n * (2 * n - 1); };
    case 4:
      return [](size_t n) { return n * (5 * n - 3) / 2; };
    default:
      return [](size_t n) { return n * (3 * n - 2); };
  }
}

bool search(size_t depth, size_t start, size_t initial, std::vector<bool> done, std::vector<StartPoint> const &startpoints)
{
  if (depth == 7 && initial == start)
    return true;

  for (size_t type = 0; type != done.size(); ++type)
  {
    if (done[type])
      continue;

    done[type] = true;

    for (auto end : startpoints[start].to[type])
    {
      if (search(depth + 1, end, initial, done, startpoints))
      {
        std::cout << std::setw(depth * 2) << start << static_cast<size_t>(end) << '\n';
        return true;
      }
    }

    done[type] = false;
  }

  return false;
}

int main()
{
  std::vector<StartPoint> startpoints(101);

  std::vector<std::pair<size_t, size_t>> between{
    {45, 140},
    {32, 99},
    {26, 81},
    {23, 70},
    {21, 63},
    {19, 58}
  };

  for (size_t idx = 0; idx != between.size(); ++idx)
  {
    auto fn = figurate(idx);

    for (size_t n = between[idx].first; n <= between[idx].second; ++n)
    {
      size_t num = fn(n);
      size_t fst = num / 100;
      size_t snd = num % 100;

      if (snd < 10)
        continue;

      startpoints[fst].to[idx].push_back(snd);
    }
  }

  for (size_t start = 10; start != 100; ++start)
    search(1, start, start, {false, false, false, false, false, false}, startpoints);
}