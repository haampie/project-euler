#include <iostream>
#include <tuple>
#include <vector>

void pythagorean(size_t max, size_t a, size_t b, size_t c, std::vector<size_t> &perimeter)
{
  if (a + b + c > max)
    return;

  perimeter.push_back(a + b + c);

  pythagorean(max, a + 2 * c - 2 * b, 2 * a + 2 * c - b, 2 * a + 3 * c - 2 * b, perimeter);
  pythagorean(max, a + 2 * b + 2 * c, 2 * a + b + 2 * c, 2 * a + 2 * b + 3 * c, perimeter);
  pythagorean(max, 2 * b + 2 * c - a, b + 2 * c - 2 * a, 2 * b + 3 * c - 2 * a, perimeter);
}

int main()
{
  std::vector<size_t> v;
  pythagorean(1000, 3, 4, 5, v);

  size_t max = 0;
  size_t max_idx = 0;

  for (size_t p = 1; p != 1000; ++p)
  {
    for (size_t idx = 0; idx != v.size(); ++idx)
    {
      if (p % v[idx] != 0)
      {
        if (idx > max) {
          max = idx;
          max_idx = p;
          std::cout << v[idx] << '\n';
        }
        break;
      }
    }
  }

  std::cout << "p = " << max_idx << '\n';

}