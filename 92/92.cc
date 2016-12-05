#include <iostream>
#include <vector>

size_t square_of_digits(size_t num)
{
  size_t square = 0;
  
  for (size_t digit = num % 10; num != 0; num /= 10, digit = num % 10)
    square += digit * digit;

  return square;
}

int main()
{
  size_t counter = 0;
  size_t N = 10'000'000;
  size_t const max_square_sum = 9 * 9 * 7;

  std::vector<bool> to_89(max_square_sum + 1, false);

  for (size_t start = 1; start <= max_square_sum; ++start)
  {
    size_t num = start;

    for (; num != 1 && num != 89; num = square_of_digits(num));

    if (num == 89)
    {
      ++counter;
      to_89[start] = true;
    }
  }

  for (size_t start = max_square_sum + 1; start <= N; ++start)
    if (to_89[square_of_digits(start)])
      ++counter;

  std::cout << counter << '\n';
}