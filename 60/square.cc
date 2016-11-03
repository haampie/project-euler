#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

// 10^k p1 + p2 mod 30 = 10*(p1 mod 30) + (p2 mod 30) mod 30
// 10^k p2 + p1 mod 30 = 10*(p2 mod 30) + (p1 mod 30) mod 30
// Idea: take two potential primes p1 & p2, not divisable
// by 2, 3 and 5, and see whether 10^k p1 + p2 and vice versa
// is part of a 30-wheel modulo class.

inline bool is_candidate(size_t x, size_t y, std::vector<size_t> const &wheel)
{
  return std::binary_search(wheel.begin(), wheel.end(), (10 * x + y) % 30)
    && std::binary_search(wheel.begin(), wheel.end(), (10 * y + x) % 30);
}

int main()
{

  std::vector<size_t> wheel{1, 7, 11, 13, 17, 19, 23, 29};

  std::cout << std::setw(4) << ' ';

  for (size_t y = 0; y != wheel.size(); ++y)
    std::cout << std::setw(4) << wheel[y];

  std::cout << '\n';
  
  for (size_t y = 0; y != wheel.size(); ++y)
  {
    std::cout << std::setw(4) << wheel[y];
    for (size_t x = 0; x != wheel.size(); ++x)
    {
      std::cout << std::setw(4) << (is_candidate(wheel[x], wheel[y], wheel) ? 'y' : 'n');
    }

    std::cout << '\n';
  }
  std::cout << '\n';
}