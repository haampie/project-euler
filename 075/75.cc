#include <iostream>
#include <vector>

class RightTriangleCounter
{
  size_t max;
  size_t total;
  std::vector<size_t> perimeters;
  std::vector<size_t> combinations_of_length;

public:
  RightTriangleCounter(size_t max)
  : max(max), total(0), combinations_of_length(max + 1, 0)
  {
    generate_base(3, 4, 5);

    for (auto perimeter : perimeters)
      for (size_t multiple = perimeter; multiple <= max; multiple += perimeter)
        ++combinations_of_length[multiple];

    for (auto combinations : combinations_of_length)
      if (combinations == 1)
        ++total;
  }

  inline size_t count() const
  {
    return total;
  }
private:
  void generate_base(size_t a, size_t b, size_t c)
  {
    if (a + b + c > max)
      return;

    perimeters.push_back(a + b + c);

    generate_base(a + 2 * c - 2 * b, 2 * a + 2 * c - b, 2 * a + 3 * c - 2 * b);
    generate_base(a + 2 * b + 2 * c, 2 * a + b + 2 * c, 2 * a + 2 * b + 3 * c);
    generate_base(2 * b + 2 * c - a, b + 2 * c - 2 * a, 2 * b + 3 * c - 2 * a);
  }
};

int main()
{
  RightTriangleCounter counter(1500000);
  std::cout << counter.count() << '\n';
}