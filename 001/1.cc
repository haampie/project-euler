#include <iostream>

using namespace std;

constexpr size_t triangular(size_t N)
{
  return (N * (N + 1)) / 2;
}

constexpr size_t dividable(size_t N, size_t divisor)
{
  return N / divisor;
}

int main()
{
  size_t const upper = 999;
  cout << 3 * triangular(dividable(upper, 3))
    + 5 * triangular(dividable(upper, 5))
    - 15 * triangular(dividable(upper, 15)) << '\n';
}