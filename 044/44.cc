#include <iostream>
#include <vector>

using namespace std;

inline size_t pentagonal(size_t n)
{
  return n * (3 * n - 1) / 2;
}

bool ispentagonal(size_t num)
{
  for (size_t n = 1; n < 10000; ++n)
  {
    size_t p = pentagonal(n);

    if (p == num)
      return true;
    if (p > num)
      return false;
  }

  return false;
}

int main()
{
  std::vector<size_t> nums;

  for (size_t fst = 6000; fst != 20000; ++fst)
  {
    const size_t c = pentagonal(fst);
    std::cout << c << '\n';

    for (size_t snd = fst + 1; snd != 20000; ++snd)
    {
      const size_t Pm = pentagonal(snd);

      if (ispentagonal(c + Pm) && ispentagonal(c + 2 * Pm))
      {
        std::cout << c << '\n';
        return 0;
      }
    }
  }
}