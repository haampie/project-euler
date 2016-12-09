#include <iostream>
#include <vector>
#include <chrono>

size_t pow(size_t b, size_t e)
{
  size_t num = 1;

  for (size_t idx = 1; idx <= e; ++idx)
    num *= b;

  return num;
}

void explore(size_t depth, size_t digits, size_t total, std::vector<bool> &occupied, std::vector<size_t> const &divs)
{
  if (depth == divs.size())
  {
    for (size_t idx = 0; idx != 10; ++idx)
      if (occupied[idx] == false)
        std::cout << idx << ' ';
    std::cout << total << '\n';
    return;
  }

  for (size_t idx = 0; idx != 10; ++idx)
  {
    if (!occupied[idx] && (digits / 10 + idx*100) % divs[depth] == 0)
    {
      occupied[idx ] = true;
      explore(depth + 1, digits / 10 + 100 * idx, total + idx * pow(10, depth + 3), occupied, divs);
      occupied[idx ] = false;
    }
  }
}

int main()
{
  std::chrono::time_point<std::chrono::system_clock> start, end;
  start = std::chrono::system_clock::now();
  for (size_t a = 17; a < 1000; a += 17)
  {
    std::vector<bool> occupied(10, false);
    std::vector<size_t> dividers{13, 11, 7, 5, 3, 2};
    occupied[a % 10] = true;
    
    if (occupied[(a / 10) % 10])
      continue;
    
    occupied[(a / 10) % 10] = true;

    if (occupied[a / 100])
      continue;

    occupied[a / 100] = true;

    explore(0, a, a, occupied, dividers);
  }

  end = std::chrono::system_clock::now();
  std::chrono::duration<double> elapsed_seconds = end-start;

  std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
}