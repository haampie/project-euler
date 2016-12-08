#include <iostream>
#include <string>
#include <map>
#include <vector>

bool anagram(std::string const &lhs, std::string const &rhs)
{
  if (lhs.size() != rhs.size())
    return false;

  int8_t count[26] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

  for (char ch : lhs)
    ++count[ch - 'A'];

  for (char ch : rhs)
    if (count[ch - 'A']-- == 0)
      return false;

  return true;
}

int main()
{
  std::map<size_t, std::vector<std::string>> values;

  std::istream_iterator<std::string> eos;

  for (std::istream_iterator<std::string> it(std::cin); it != eos; ++it)
  {
    size_t sum = 0;

    for (auto character : *it)
    {
      size_t char_value = character - 'A' + 12343;
      sum += char_value * char_value;
    }

    auto item = values.find(sum);

    if (item != values.end())
      item->second.push_back(*it);
    else
      values[sum] = std::vector<std::string>{*it};
  }

  std::vector<std::pair<std::string, std::string>> anagrams;

  size_t count = 0;
  for (auto item : values)
  {
    if (item.second.size() == 1)
      continue;

    ++count;
    
    for (size_t lhs = 0; lhs < item.second.size(); ++lhs)
      for (size_t rhs = lhs + 1; rhs < item.second.size(); ++rhs)
        if (anagram(item.second[lhs], item.second[rhs]))
          anagrams.emplace_back(item.second[lhs], item.second[rhs]);
  }

  for (auto pair : anagrams)
    std::cout << pair.first << ' ' << pair.second << '\n';

  std::cout << count << '\n' << anagrams.size() << '\n';

  for (size_t n = 1; n < 100000; ++n)
    std::cout << n * n << '\n';
}