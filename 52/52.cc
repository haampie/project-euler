#include <iostream>
#include <chrono>

bool is_permutation(size_t a, size_t b)
{
  char digits[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

  for (; a != 0; a /= 10)
    ++digits[a % 10];

  for (; b != 0; b /= 10)
    if (digits[b % 10]-- == 0)
      return false;

  return true;
}

inline bool multiples_are_permutations(size_t num)
{
  for (size_t multiple = 2; multiple != 7; ++multiple)
    if (!is_permutation(num, num * multiple))
      return false;

  return true;
}

size_t search()
{
  for (size_t start = 10;; start *= 10)
    for (size_t num = start; 6 * num < 10 * start; ++num)
      if (multiples_are_permutations(num))
        return num;

  return 0;
}

int main()
{
  auto t1 = std::chrono::high_resolution_clock::now();
  size_t num = search();
  auto t2 = std::chrono::high_resolution_clock::now();

  std::chrono::duration<double, std::milli> fp_ms = t2 - t1;

  std::cout << num << "\nTook: " << fp_ms.count() << '\n';
}