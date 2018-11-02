#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

size_t term(size_t const n)
{
  size_t total = 1;
  size_t power = n;

  for (size_t idx = 1; idx <= 5; ++idx)
  {
    total += power * (n - 1);
    power *= n * n;
  }

  return total;
}

std::vector<size_t> sequence(size_t N)
{
  std::vector<size_t> seq;
  for (size_t n = 1; n <= N; ++n)
  {
    seq.push_back(term(n));
  }

  return seq;
}

double extrapolate(std::vector<size_t> const &seq, int64_t order, int64_t x)
{
  double total = 0;

  for (int64_t n = 1; n <= order; ++n)
  {
    double numerator = 1.0;
    double denominator = 1.0;
    
    for (int64_t m = 1; m <= order; ++m)
    {
      if (n == m)
        continue;

      numerator *= x - m;
      denominator *= n - m;
    }

    total += numerator * seq[n - 1] / denominator;
  }

  return total;
}

int main()
{
  auto seq = sequence(10);
  double sum = 0;

  for (size_t order = 1; order <= 10; ++order)
    sum += extrapolate(seq, order, order + 1);

  std::cout << static_cast<size_t>(std::round(sum)) << '\n';
}