#include <iostream>
#include <array>
#include <algorithm>
#include <iterator>

bool explore(size_t idx, std::array<size_t, 10> &values, std::array<bool, 10> &available)
{
  if (idx >= 10) {
    if (values[1] + values[8] + values[9] != values[0] + values[1] + values[2] || values[9] < values[0])
      return false;
    return true;
  }

  for (size_t num = 10; num != 0; --num)
  {
    if (num == 10 && (idx == 1 || idx == 2 || idx == 4 || idx == 6 || idx == 8))
      continue;

    if (available[num - 1])
    {
      if (idx == 3 || idx == 5 || idx == 7) {

        if (num < values[0])
          continue;
        
        size_t sum = values[0] + values[1] + values[2];
        size_t part = num + values[idx - 1];

        if (part >= sum || sum - part == num)
          continue;

        if (sum - part > 9)
          break;

        if (! available[sum - part - 1])
          continue;

        available[num - 1] = false;
        available[sum - part - 1] = false;
        values[idx] = num;
        values[idx + 1] = sum - part;
        if (explore(idx + 2, values, available))
          return true;
        available[sum - part - 1] = true;
        available[num - 1] = true;
      } else {
        available[num - 1] = false;
        values[idx] = num;
        if (explore(idx + 1, values, available))
          return true;
        available[num - 1] = true;
      }
    }
  }

  return false;
}

int main()
{
  std::array<bool, 10> available{true, true, true, true, true, true, true, true, true, true};
  std::array<size_t, 10> values{0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  explore(0, values, available);

  std::cout 
    << values[0] << values[1] << values[2]
    << values[3] << values[2] << values[4]
    << values[5] << values[4] << values[6]
    << values[7] << values[6] << values[8]
    << values[9] << values[8] << values[1]
    << '\n';
}