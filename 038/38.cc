#include <iostream>
#include <vector>

bool unique(size_t a, size_t b)
{
  std::vector<bool> u(10, false);
  u[0] = true;

  while(a != 0)
  {
    size_t digit = a % 10;
    
    if (u[digit])
      return false;

    u[digit] = true;
    a /= 10;
  }

  while(b != 0)
  {
    size_t digit = b % 10;
    
    if (u[digit])
      return false;

    u[digit] = true;
    b /= 10;
  }

  return true;
}

int main()
{
  for (size_t num = 9876; num != 0; --num)
    if (unique(num, num * 2))
      std::cout << num << num * 2 << '\n';
}