#include <iostream>
#include <tuple>

using pell = std::pair<size_t, size_t>;

inline pell next(pell const &solution)
{
  return {
    2 * solution.first + 3 * solution.second, 
    2 * solution.second + solution.first
  };
}

int main()
{
  size_t sum = 0;
  size_t const max = 1000000000ul;
  size_t perimeter = 0;

  // Initial solution to Pells equation x^2 - 3y^2 = 1 
  // producing a valid triangle
  pell solution{7, 4};

  while (true)
  {
    // Longer side
    perimeter = 2 * (solution.first + 1);
    if (perimeter > max) break;
    sum += perimeter;
    solution = next(solution);

    // Smaller side
    perimeter = 2 * (solution.first - 1);
    if (perimeter > max) break;
    sum += perimeter;
    solution = next(solution);
  }

  std::cout << sum << '\n';
}