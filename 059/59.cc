#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>

using namespace std;

int main()
{
  size_t const length = 3;
  vector<size_t> numbers;
  vector<size_t> keys(length);

  copy(istream_iterator<size_t>(cin), istream_iterator<size_t>(), back_inserter(numbers));

  for (size_t start = 0; start != length; ++start)
  {
    vector<size_t> count(128, 0);

    for (size_t idx = start; idx < numbers.size(); idx += length)
      ++count[numbers[idx]];

    keys[start] = ' ' xor distance(count.begin(), max_element(count.begin(), count.end()));
  }

  size_t sum = 0;

  for (size_t idx = 0; idx != numbers.size(); ++idx)
   sum += numbers[idx] xor keys[idx % length];

  cout << sum << '\n';
}