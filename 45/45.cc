#include <iostream>

int main()
{
  size_t t_idx = 285;
  size_t p_idx = 165;
  size_t h_idx = 143;

  size_t t_val = 40755;
  size_t p_val = 40755;
  size_t h_val = 40755;

  do
  {
    h_val += 4 * h_idx + 1;
    ++h_idx;

    while (p_val < h_val)
    {
      p_val += 3 * p_idx + 1;
      ++p_idx;
    }

    while (t_val < h_val)
    {
      t_val += t_idx + 1;
      ++t_idx;
    }
  } while(! (h_val == t_val && t_val == p_val));

  std::cout << t_idx << ' ' << h_idx << ' ' << p_idx << ": " << h_val << '\n';
}