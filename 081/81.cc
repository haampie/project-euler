#include <iostream>
#include <vector>
#include <limits>
#include <iterator>
#include <algorithm>
#include <numeric>

using namespace std;

int main()
{
  size_t const N = 80;

  std::vector<size_t> sum;

  copy_n(istream_iterator<size_t>(cin), N, back_inserter(sum));
  partial_sum(sum.begin(), sum.end(), sum.begin());

  for (size_t y = 1; y != N; ++y)
  {
    sum[0] += *istream_iterator<size_t>(cin);

    transform(sum.begin() + 1, sum.end(), sum.begin(), sum.begin() + 1, [](size_t a, size_t b) {
      return *istream_iterator<size_t>(cin) + min(a, b);
    });
  }

  std::cout << sum.back() << '\n';
}