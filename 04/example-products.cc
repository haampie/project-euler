#include <iostream>
#include <set>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>

struct Duo {
  size_t a;
  size_t b;
  size_t prod;

  Duo(size_t a, size_t b)
    : a(a), b(b), prod(a * b)
  {}
};

bool palindrome(size_t N)
{
  size_t num = N;
  size_t rev = 0;

  while (num > 0)
  {
    rev = rev * 10 + num % 10;
    num /= 10;
  }

  return rev == N;
}

int main()
{
  std::vector<size_t> palindromes;

  size_t const max = 9999999;
  size_t number = 10;

  palindromes.reserve(number);

  auto comp = [](Duo const & lhs, Duo const & rhs) {
    return lhs.prod < rhs.prod;
  };

  std::set<size_t> products;
  std::priority_queue<Duo, std::vector<Duo>, decltype(comp)> q(comp);

  products.insert(max * max);
  q.push({max, max});

  while ( !q.empty() && number > 0) {
    auto item = q.top();
    q.pop();

    if (palindrome(item.prod)) {
      --number;
      palindromes.push_back(item.prod);
      std::cout << '(' << item.a << ", " << item.b << ") = " << item.prod << '\n';
    }

    if (item.b > 0) {
      Duo numbers{item.a, item.b - 1};
      if (products.count(numbers.prod) == 0) {
        products.insert(numbers.prod);
        q.push(std::move(numbers));
      }
    }

    if (item.a != item.b && item.a > 0) {
      Duo numbers{item.a - 1, item.b};
      if (products.count(numbers.prod) == 0) {
        products.insert(numbers.prod);
        q.push(std::move(numbers));
      }
    }
  }

  std::cout << "Sorted? " << std::is_sorted(palindromes.rbegin(), palindromes.rend()) << '\n';
}