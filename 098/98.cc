#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <deque>
#include <algorithm>
#include <numeric>
#include <iterator>

template <typename T>
std::vector<size_t> sort_indices(std::deque<T> const &v)
{
  // initialize original index locations
  std::vector<size_t> indices(v.size());
  std::iota(indices.begin(), indices.end(), 0);

  // sort indexes based on comparing values in v
  std::sort(indices.begin(), indices.end(), [&v](size_t fst, size_t snd)
  {
    return v[fst] < v[snd];
  });

  return indices;
}

template <size_t N> class Alphabet
{
  std::deque<uint8_t> string;
  size_t hash_cache = 0;

public:
  Alphabet(std::string const &str)
  {
    for (char ch : str)
      string.push_back(ch - 'A');
  }

  Alphabet(size_t num)
  {
    for (; num != 0; num /= 10)
      string.push_front(num % 10);
  }

  bool anagram_of(Alphabet const &rhs) const
  {
    if (string.size() != rhs.string.size())
      return false;

    std::array<int8_t, N> count;
    count.fill(0);

    for (uint8_t ch : string)
      ++count[ch];

    for (uint8_t ch : rhs.string)
      if (count[ch]-- == 0)
        return false;

    return true;
  }

  std::vector<size_t> transform(Alphabet const &rhs) const
  {
    auto from = sort_indices(string);
    auto to = sort_indices(rhs.string);

    std::vector<size_t> form_inverse(from.size());

    for (size_t idx = 0; idx < from.size(); ++idx)
      form_inverse[from[idx]] = idx;

    for (size_t idx = 0; idx < from.size(); ++idx)
      from[idx] = to[form_inverse[idx]];

    return from;
  }

  bool equal_under_transform(std::vector<size_t> const &mapping, Alphabet const &rhs) const
  {
    for (size_t idx = 0; idx < mapping.size(); ++idx)
      if (string[idx] != rhs.string[mapping[idx]])
        return false;

    return true;
  }

  std::string to_string() const
  {
    std::string str;

    for (auto ch : string)
      str.push_back('A' + ch);

    return str;
  }

  size_t to_num() const
  {
    size_t num = 0;
    for (auto it = string.begin(); it != string.end(); ++it)
      num = 10 * num + *it;

    return num;
  }

  inline size_t hash()
  {
    if (hash_cache != 0)
      return hash_cache;

    for (auto ch : string)
    {
      size_t char_value = ch + 12343;
      hash_cache += char_value * char_value;
    }

    return hash_cache;
  }

  inline size_t size() const
  {
    return string.size();
  }
};

template <class T> class AnagramLister
{
  std::map<size_t, std::vector<T>> values;

public:
  void add(T &&word)
  {
    auto item = values.find(word.hash());

    if (item != values.end())
      item->second.emplace_back(word);
    else
      values[word.hash()] = {word};
  }

  std::vector<std::pair<T, T>> anagrams() const
  {
    std::vector<std::pair<T, T>> list;

    for (auto item : values)
    {
      if (item.second.size() == 1)
        continue;

      for (size_t lhs = 0; lhs < item.second.size(); ++lhs)
        for (size_t rhs = lhs + 1; rhs < item.second.size(); ++rhs)
          if (item.second[lhs].anagram_of(item.second[rhs]))
            list.emplace_back(item.second[lhs], item.second[rhs]);
    }

    return list;
  }
};

int main()
{
  // Strings from stdin
  AnagramLister<Alphabet<26>> lister;

  std::string str;
  while (std::cin >> str)
    lister.add(Alphabet<26>(str));

  // Squares.
  AnagramLister<Alphabet<10>> numbers;

  for (size_t n = 1; n * n < 1000000000; ++n)
    numbers.add(Alphabet<10>(n * n));

  auto number_pairs = numbers.anagrams();

  for (auto const &words : lister.anagrams())
  {
    // Compute transformation from words.first -> words.second.
    auto transform1 = words.first.transform(words.second);
    auto transform2 = words.second.transform(words.first);

    for (auto const &candidate : number_pairs)
    {
      if (words.first.size() < candidate.first.size())
        break;

      if (words.first.size() > candidate.first.size())
        continue;

      if (candidate.first.equal_under_transform(transform1, candidate.second))
      {
         std::cout << words.first.to_string() << ' ' 
                  << words.second.to_string() << ' '
                  << candidate.first.to_num() << ' '
                  << candidate.second.to_num() << ' '
                  << '\n';
      }
      if (candidate.first.equal_under_transform(transform2, candidate.second))
      {
         std::cout << words.second.to_string() << ' ' 
                  << words.first.to_string() << ' '
                  << candidate.first.to_num() << ' '
                  << candidate.second.to_num() << ' '
                  << '\n';
      }
    }
  }

  // for (auto const &pair : numbers.anagrams())
  //   std::cout << pair.first.to_num() << ' ' << pair.second.to_num() << '\n';
}