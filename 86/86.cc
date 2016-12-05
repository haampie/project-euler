#include <iostream>
#include <tuple>
#include <vector>
#include <set>

using namespace std;

void pythagorean(size_t max, size_t a, size_t b, size_t c, vector<tuple<size_t, size_t, size_t>> &triples)
{
  if (c > 3*max)
    return;

  if (a <= 2*max && b <= 2*max)
    triples.push_back(a < b ? make_tuple(a, b, c) : make_tuple(b, a, c));

  pythagorean(max, a + 2 * c - 2 * b, 2 * a + 2 * c - b, 2 * a + 3 * c - 2 * b, triples);
  pythagorean(max, a + 2 * b + 2 * c, 2 * a + b + 2 * c, 2 * a + 2 * b + 3 * c, triples);
  pythagorean(max, 2 * b + 2 * c - a, b + 2 * c - 2 * a, 2 * b + 3 * c - 2 * a, triples);
}

tuple<size_t, size_t, size_t> order(size_t a, size_t b, size_t c)
{
  if (a < b)
  {
    if (b < c)
      return make_tuple(a, b, c);

    if (a < c)
      return make_tuple(a, c, b);

    return make_tuple(c, a, b);
  }

  if (a < c)
    return make_tuple(b, a, c);

  if (b < c)
    return make_tuple(b, c, a);

  return make_tuple(c, b, a);
}

int main()
{
  size_t const M = 1818;

  set<tuple<size_t, size_t, size_t>> instances;
  vector<tuple<size_t, size_t, size_t>> triples;

  pythagorean(M, 3, 4, 5, triples);

  for (auto triple : triples)
  {
    for (size_t multiple = 1; multiple * get<1>(triple) <= M; ++multiple)
      for (size_t y = 1; y <= (multiple * get<0>(triple)) / 2; ++y)
        if (y <= multiple * get<1>(triple) && multiple * get<0>(triple) - y <= multiple * get<1>(triple))
          instances.insert(order(y, multiple * get<0>(triple) - y, multiple * get<1>(triple)));

    for (size_t multiple = 1; multiple * get<0>(triple) <= M; ++multiple)
      for (size_t y = 1; y <= (multiple * get<1>(triple)) / 2; ++y)
        if (y <= multiple * get<0>(triple) && multiple * get<1>(triple) - y <= multiple * get<0>(triple))
          instances.insert(order(y, multiple * get<1>(triple) - y, multiple * get<0>(triple)));
  }

  std::cout << instances.size() << '\n';
}