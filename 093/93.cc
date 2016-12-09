#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <iterator>

class Frac {
  friend std::ostream &operator<<(std::ostream &os, Frac frac);
  int num;
  int den;

public:
  Frac(int numerator, int denominator)
  {
    int d = gcd(abs(numerator), abs(denominator));
    num = numerator / d;
    den = denominator / d;
    
    if (den < 0)
    {
      num *= -1;
      den *= -1;
    }
  }

  Frac(int num)
  : num(num), den(1)
  {}

  Frac operator+(Frac const &rhs) const
  {
    return {num * rhs.den + den * rhs.num, rhs.den * rhs.den};
  }

  Frac operator-(Frac const &rhs) const
  {
    return {num * rhs.den - den * rhs.num, rhs.den * rhs.num};
  }

  Frac operator*(Frac const &rhs) const
  {
    return {num * rhs.num, den * rhs.den};
  }

  Frac operator/(Frac const &rhs) const
  {
    return {num * rhs.den, den * rhs.num};
  }

  Frac operator-() const
  {
    return {-num, den};
  }

  bool operator<(Frac const &rhs) const
  {
    return num * rhs.den < rhs.num * den;
  }

  inline bool zero() const
  {
    return num == 0;
  }

  inline bool pos_integer() const
  {
    return den == 1 && num >= 1;
  }

  inline int numerator() const
  {
    return num;
  }
private:
  int gcd(int a, int b)
  {
    return b == 0 ? a : gcd(b, a % b);
  }
};

std::ostream &operator<<(std::ostream &os, Frac frac)
{
  return os << frac.num << '/' << frac.den;
}

std::set<Frac> combis(std::set<Frac> const &lhs, std::set<Frac> const &rhs)
{
  std::set<Frac> results;

  for (auto left : lhs)
  {
    for (auto right : rhs)
    {
      results.emplace(left + right);
      results.emplace(left * right);
      results.emplace(left - right);
      results.emplace(right - left);

      if (!right.zero())
        results.emplace(left / right);

      if (!left.zero())
        results.emplace(right / left);
    }
  }

  return results;
}

std::set<Frac> stuff(std::vector<size_t> remaining)
{
  if (remaining.size() == 1)
    return {Frac(remaining[0])};

  std::set<Frac> results;

  if (remaining.size() == 4)
  {
    auto a1 = stuff({remaining[0], remaining[1], remaining[2]});
    auto a2 = stuff({remaining[3]});
    auto a = combis(a1, a2);
    results.insert(a.begin(), a.end());

    auto b1 = stuff({remaining[0], remaining[1], remaining[3]});
    auto b2 = stuff({remaining[2]});
    auto b = combis(b1, b2);
    results.insert(b.begin(), b.end());
    
    auto c1 = stuff({remaining[0], remaining[2], remaining[3]});
    auto c2 = stuff({remaining[1]});
    auto c = combis(c1, c2);
    results.insert(c.begin(), c.end());

    auto d1 = stuff({remaining[1], remaining[2], remaining[3]});
    auto d2 = stuff({remaining[0]});
    auto d = combis(d1, d2);
    results.insert(d.begin(), d.end());
    
    auto e1 = stuff({remaining[0], remaining[1]});
    auto e2 = stuff({remaining[2], remaining[3]});
    auto e = combis(e1, e2);
    results.insert(e.begin(), e.end());
    
    auto f1 = stuff({remaining[0], remaining[2]});
    auto f2 = stuff({remaining[1], remaining[3]});
    auto f = combis(f1, f2);
    results.insert(f.begin(), f.end());
    
    auto g1 = stuff({remaining[0], remaining[3]});
    auto g2 = stuff({remaining[1], remaining[2]});
    auto g = combis(g1, g2);
    results.insert(g.begin(), g.end());

    return results;
  }

  if (remaining.size() == 3)
  {
    auto a1 = stuff({remaining[0], remaining[1]});
    auto a2 = stuff({remaining[2]});
    auto a = combis(a1, a2);
    results.insert(a.begin(), a.end());

    auto b1 = stuff({remaining[0], remaining[2]});
    auto b2 = stuff({remaining[1]});
    auto b = combis(b1, b2);
    results.insert(b.begin(), b.end());

    auto c1 = stuff({remaining[1], remaining[2]});
    auto c2 = stuff({remaining[0]});
    auto c = combis(c1, c2);
    results.insert(c.begin(), c.end());
  }

  if (remaining.size() == 2)
  {
    auto a1 = stuff({remaining[0]});
    auto a2 = stuff({remaining[1]});
    auto a = combis(a1, a2);
    results.insert(a.begin(), a.end());
  }

  return results;
}

int main()
{
  size_t max = 0;
  for (size_t a = 1; a < 10; ++a)
  {
    for (size_t b = a + 1; b < 10; ++b)
    {
      for (size_t c = b + 1; c < 10; ++c)
      {
        for (size_t d = c + 1; d < 10; ++d)
        {
          std::set<Frac> nums = stuff({a, b, c, d});

          size_t expected = 1;
          size_t count = 0;

          std::cout << a << ' ' << b << ' ' << c << ' ' << d << ": ";

          for (auto unique : nums)
          {
            if (unique.pos_integer())
            {
              std::cout << unique.numerator() << ' ';
              if (unique.numerator() != expected)
                break;

              ++count;
              ++expected;
            }
          }

          std::cout << count << '\n';

          if (count > max)
          {
            std::cout << "(max)\n";
            max = expected;
          }
        }
      }
    }
  }

  std::cout << "max = " << max << '\n';
}