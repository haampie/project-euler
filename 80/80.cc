#include <iostream>
#include <vector>
#include <deque>
#include <iterator>
#include <algorithm>

bool is_smaller(std::deque<int32_t> const &lhs, std::deque<int32_t> const &rhs)
{
  if (lhs.size() < rhs.size())
    return true;

  if (lhs.size() > rhs.size())
    return false;

  for (size_t idx = lhs.size(); idx != 0; --idx)
  {
    if (lhs[idx - 1] > rhs[idx - 1])
      return false;

    if (lhs[idx - 1] < rhs[idx - 1])
      return true;
  }

  return false;
}

bool equals_zero(std::deque<int32_t> const &num)
{
  for (size_t idx = 0; idx != num.size(); ++idx)
    if (num[idx] != 0)
      return false;

  return true;
}

std::deque<int32_t> &subtract(std::deque<int32_t> &lhs, std::deque<int32_t> const &rhs)
{
  for (size_t idx = 0; idx != rhs.size(); ++idx)
    if (idx == lhs.size())
      lhs.push_back(-rhs[idx]);
    else
      lhs[idx] -= rhs[idx];

  // Fix underflow
  for (size_t idx = 0; idx + 1 != lhs.size(); ++idx)
    if (lhs[idx] < 0)
    {
      lhs[idx] = 10 + (lhs[idx] % 10);
      lhs[idx + 1] += lhs[idx] / 10 - 1;
    }

  while (lhs.size() > 0 && lhs.back() == 0)
    lhs.pop_back();

  return lhs;
}

void output(std::deque<int32_t> const &a)
{
  std::copy(a.rbegin(), a.rend(), std::ostream_iterator<int32_t>(std::cout));
}

int main()
{

  size_t max_precision = 100;

  std::deque<int32_t> a{1,7};
  std::deque<int32_t> b{3};
  std::deque<int32_t> c;

  std::deque<int32_t> window;
  std::deque<int32_t> divisor(b.begin(), b.end());

  // initialize
  size_t idx = a.size();
  while (is_smaller(window, divisor))
  {
    if (idx == 0)
    {
      window.push_front(0);
      continue;
    }

    window.push_front(a[idx - 1]);
    --idx;
  }

  while(c.size() < max_precision && !equals_zero(window))
  {
    size_t times = 0;

    for (;!is_smaller(window, divisor); ++times)
      subtract(window, divisor);
    
    c.push_front(times);

    if (idx == 0)
    {
      window.push_front(0);
      continue;
    }

    window.push_front(a[idx - 1]);
    --idx;
  }

  // Rounding...
  if (!equals_zero(window)) {
    size_t times = 0;

    for (;!is_smaller(window, divisor); ++times)
      subtract(window, divisor);

    if (times >= 5)
      ++c[0];
  }

  output(c);
  std::cout << '\n';
}