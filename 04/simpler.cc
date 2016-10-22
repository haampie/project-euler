#include <iostream>
#include <queue>
#include <set>
#include <functional>

unsigned char length(size_t N)
{
  // 2^64 == 9'223'372'036'854'775'807
  if (N > 1'000'000'000)
}

bool palindrome(size_t N)
{
  // Filter 1 / 11 of even-length numbers
  if (length(N) % 2 == 0 && N % 11 != 0)
    return false;

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
  size_t const max = 999999;
  size_t const number = 10;

  std::priority_queue<size_t, std::vector<size_t>, std::greater<size_t> > palindromes;
  std::set<size_t> unique;

  for (size_t i = 0; i != number; ++i) {
    palindromes.push(0);
  }

  for (size_t left = max; left * max > palindromes.top(); --left)
  {
    for (size_t right = max; left * right > palindromes.top(); --right)
    {
      size_t const prod = left * right;

      if (palindrome(prod) && unique.count(prod) == 0)
      {
        palindromes.pop();
        palindromes.push(prod);
        unique.insert(prod);
      }
    }
  }

  while (!palindromes.empty())
  {
    std::cout << palindromes.top() << '\n';
    palindromes.pop();
  }
}