#include <iostream>

using namespace std;

int main()
{
  size_t const below = 4'000'000ul;

  size_t sum = 0;
  size_t prev = 0;
  size_t next = 1;

  while (next < below)
  {
    if (next % 2 == 0)
      sum += next;
    
    size_t tmp = next;
    next = next + prev;
    prev = tmp; 
  }

  cout << sum << '\n';
}