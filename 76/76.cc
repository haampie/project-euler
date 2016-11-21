#include <iostream>
#include <algorithm>
#include <vector>
#include <chrono>

int main()
{
  auto start = std::chrono::high_resolution_clock::now();

  const size_t N = 100;
  std::vector<std::vector<size_t>> parts;

  for (size_t y = 0; y <= N; ++y)
    parts.push_back(std::vector<size_t>(y + 1, 0));

  parts[0][0] = 1;

  for (size_t y = 1; y <= N; ++y)
    for (size_t x = 1; x <= y; ++x)
      parts[y][x] = parts[y][x - 1] + parts[y - x][std::min(x, y - x)];

  std::cout << parts[N][N - 1] << '\n';
  
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed_seconds = end-start;
  std::chrono::duration<double> diff = end-start;
  std::cout << diff.count() << " s\n";
}