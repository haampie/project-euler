#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

std::vector<size_t> expansion_of_square_root(size_t square)
{
  size_t integer_part = 1;

  for (; integer_part * integer_part + 2 * integer_part < square; ++integer_part);

  if (integer_part * integer_part == square)
    return {integer_part};

  std::vector<size_t> expansion;
  expansion.push_back(integer_part);

  size_t m = 0;
  size_t d = 1;

  for (size_t idx = 0; expansion[idx] != 2 * expansion[0]; ++idx)
  {
    m = d * expansion[idx] - m;
    d = (square - m * m) / d;
    expansion.push_back((integer_part + m) / d);
  }

  return expansion;
}

class Biggy {
  friend std::ostream &operator<<(std::ostream &os, Biggy const &biggy);

  std::vector<size_t> digits;

  inline void overflow()
  {
    for (size_t idx = 0; idx != digits.size(); ++idx)
    {
      size_t times = digits[idx] / 10;
      if (times != 0)
      {
        digits[idx] %= 10;
        if (idx + 1 == digits.size())
          digits.push_back(times);
        else
          digits[idx + 1] += times;
      }
    }
  }

public:

  Biggy(size_t num)
  {
    for (; num != 0; num /= 10)
      digits.push_back(num % 10);
  }

  Biggy &operator*=(Biggy const &rhs)
  {
    Biggy result(0);

    for (size_t idx = 0; idx < rhs.digits.size() + digits.size() - 1; ++idx)
    {
      size_t total = 0;
      for (size_t other = 0; other <= idx; ++other)
        if (other < digits.size() && idx - other < rhs.digits.size())
          total += digits[other] * rhs.digits[idx - other];

      result.digits.push_back(total);
    }
    result.overflow();
    digits = result.digits;

    return *this;
  }

  Biggy &operator*=(size_t num)
  {
    for(size_t idx = 0; idx != digits.size(); ++idx)
      digits[idx] *= num;

    overflow();

    return *this;
  }

  Biggy &operator+=(Biggy const &rhs)
  {
    for(size_t idx = 0; idx != rhs.digits.size(); ++idx)
    {
      if (idx == digits.size())
        digits.push_back(rhs.digits[idx]);
      else
        digits[idx] += rhs.digits[idx];
    }

    overflow();
    
    return *this;
  }

  bool operator>(Biggy const &rhs) const
  {
    if (digits.size() > rhs.digits.size())
      return true;

    if (digits.size() < rhs.digits.size())
      return false;

    for (size_t idx = digits.size(); idx != 0; --idx)
    {
      if (digits[idx - 1] > rhs.digits[idx - 1])
        return true;
      if (digits[idx - 1] < rhs.digits[idx - 1])
        return false;
    }

    return false;
  }

  inline size_t mod10() const
  {
    return digits[0];
  }

  inline size_t sum_digits() const
  {
    size_t sum = 0;
    for (size_t idx = 0; idx != digits.size(); ++idx)
      sum += digits[idx];

    return sum;
  }
};

std::ostream &operator<<(std::ostream &os, Biggy const &biggy)
{
  std::copy(biggy.digits.rbegin(), biggy.digits.rend(), std::ostream_iterator<size_t>(os, ""));
  return os;
}

void output(size_t n, Biggy const &a, Biggy const &b)
{
  std::cout << a << "^2 - " << n << " * " << b << "^2 = 1\n";
}

inline bool minusone(size_t n, Biggy const &a, Biggy const &b)
{
  return 9 == ((10 + (a.mod10() * a.mod10() % 10) - ((n % 10) * b.mod10() * b.mod10()) % 10) % 10);
}

int main()
{
  Biggy max(0);
  
  for (size_t n = 1; n <= 10'000; ++n)
  {
    auto expansion = expansion_of_square_root(n);
    
    // Skip perfect squares
    if (expansion.size() == 1)
      continue;

    Biggy prev_n(expansion[0]);
    Biggy prev_d(1);

    Biggy curr_n(expansion[1] * expansion[0] + 1);
    Biggy curr_d(expansion[1]);

    for (size_t idx = 2; idx < expansion.size() - 1; ++idx)
    {
      Biggy new_n(curr_n);
      Biggy new_d(curr_d);
      
      new_n *= expansion[idx];
      new_n += prev_n;

      new_d *= expansion[idx];
      new_d += prev_d;

      prev_n = curr_n;
      curr_n = new_n;
      prev_d = curr_d;
      curr_d = new_d;
    }

    if (minusone(n, curr_n, curr_d))
    {
      Biggy fst(curr_n);
      fst *= curr_n;

      Biggy snd(curr_d);
      snd *= curr_d;
      snd *= n;
      fst += snd;

      curr_d *= curr_n;
      curr_d *= 2;

      curr_n = fst;
    }

    if (curr_n > max)
    {
      // std::cout << n << ' ';
      max = curr_n;
      output(n, curr_n, curr_d);
    }
  }
}