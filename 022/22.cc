#include <iostream>
#include <string>

int main()
{
  size_t total = 0;
  size_t num = 1;
  std::string name;

  while(std::cin >> name)
  {
    size_t name_score = 0;

    for (char c : name)
      name_score += c - 'A' + 1;

    total += num * name_score;
    ++num;
  }

  std::cout << total << '\n';
}