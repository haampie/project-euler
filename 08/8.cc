#include <iostream>
#include <fstream>
#include <queue>
#include <string>

int main()
{
  size_t const window = 13;
  std::ifstream f("input.txt");
  std::queue<size_t> numbers;

  size_t max = 1;
  size_t product = 1;
  size_t zeros = 0;
  for (size_t idx = 0; idx != window; ++idx)
  {
    char t;
    f >> t;
    size_t num = t - '0';
    numbers.push(num);

    // Count 0's
    if (num == 0)
      ++zeros;
    else
      product *= num;
  }

  max = product;

  char t;
  while (f >> t)
  {
    size_t tail = t - '0';
    size_t head = numbers.front();
    numbers.pop();
    numbers.push(tail);

    if (head == 0)
      --zeros;
    else
      product /= head;

    if (tail == 0)
      ++zeros;
    else
      product *= tail;

    if (zeros == 0 && product > max) {
      max = product;
    }
  }

  std::cout << max << '\n';
}