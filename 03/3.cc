#include <iostream>

using namespace std;

size_t largestPrimeFactor(size_t N)
{
  size_t factor = 2;
  
  while (factor < N)
  {
    if (N % factor == 0)
    {
      N /= factor;
      cout << factor << '\n';
    } else {
      ++factor;
    }
  }

  return factor;
}

int main()
{
  const size_t N = 600'851'475'143;

  cout << largestPrimeFactor(N) << '\n';
}