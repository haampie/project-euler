#include <iostream>
#include <string>

int main()
{
  size_t count = 0;

  std::string word;
  
  while (std::cin >> word)
  {
    size_t sum = 0;
    for (char t : word)
      sum += t - 'A' + 1;

    size_t sqr = sum * 8 + 1;

    for (size_t idx = 1; idx * idx <= sqr; ++idx)
    {
      if (idx * idx == sqr)
      {
        ++count;
        std::cout << word << ": " << sum << '\n';
        break;
      }
    }
  }

  std::cout << count << '\n';
}