#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>

void generate(
  size_t depth,
  size_t const max,
  size_t start, 
  std::vector<size_t> const &list,
  std::vector<size_t> &current, 
  std::vector<std::vector<size_t>> &combis
)
{
  if (depth == max)
  {
    combis.push_back(std::vector<size_t>(current.begin(), current.end()));
    return;
  }

  for (size_t idx = start; idx + (max - depth) <= list.size(); ++idx)
  {
    current[depth] = list[idx];
    generate(depth + 1, max, idx + 1, list, current, combis);
  }
}

bool valid(std::vector<size_t> const &fst, std::vector<size_t> const &snd, std::vector<std::pair<size_t, size_t>> const &squares)
{
  std::vector<bool> enlisted(squares.size(), false);

  for (size_t a = 0; a < fst.size(); ++a)
    for (size_t b = 0; b < snd.size(); ++b)
      for (size_t c = 0; c < squares.size(); ++c)
        if ((squares[c].first == fst[a] && squares[c].second == snd[b]) || (squares[c].first == snd[b] && squares[c].second == fst[a]))
          enlisted[c] = true;

  for (size_t c = 0; c < squares.size(); ++c)
    if (!enlisted[c])
      return false;

  return true;
}

int main()
{
  std::vector<std::pair<size_t, size_t>> squares{
    {0,1}, {0,4}, {0,6}, {1,6}, {1,8}, {2,5}, {3,6}, {4,6}
  };

  std::vector<size_t> list{0,1,2,3,4,5,6,7,8,6};

  std::vector<std::vector<size_t>> combis;

  {
    std::vector<size_t> current(6, 0);
    generate(0, 6, 0, list, current, combis);
  }

  size_t num_valid = 0;

  for (size_t fst = 0; fst < combis.size(); ++fst)
    for (size_t snd = fst + 1; snd < combis.size(); ++snd)
      if (valid(combis[fst], combis[snd], squares))
        ++num_valid;

  std::cout << num_valid << '\n';
}