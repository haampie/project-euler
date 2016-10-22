#include <iostream>
#include <queue>
#include <vector>

typedef std::vector<std::vector<size_t>> Grid;

class Window {
  size_t d_length;
  size_t d_zeros;
  size_t d_product;
  size_t d_max;
  size_t d_position;
  std::queue<size_t> d_queue;

public:

  Window(size_t length)
    :
    d_length(length),
    d_zeros(0),
    d_product(1),
    d_max(0),
    d_position(0)
  {}

  inline size_t max() const
  {
    return d_max;
  }

  inline size_t curr() const
  {
    return d_product;
  }

  void add(size_t back)
  {
    ++d_position;

    d_queue.push(back);

    if (back == 0)
      ++d_zeros;
    else
      d_product *= back;

    // Don't pop or update maximum if you don't have
    // the desired length.
    // If no zero's are present, update the product.
    if (d_position == d_length && d_zeros == 0 && d_product > d_max)
      d_max = d_product;

    if (d_position <= d_length)
      return;

    // Otherwise move the window by popping.
    size_t front = d_queue.front();
    d_queue.pop();

    if (front == 0)
      --d_zeros;
    else
      d_product /= front;

    if (d_zeros == 0 && d_product > d_max)
      d_max = d_product;
  }
};

size_t horizontal(Grid const &grid, size_t size)
{
  size_t max = 0;

  for (size_t y = 0; y != grid.size(); ++y)
  {
    Window window(size);

    for (size_t x = 0; x != grid.size(); ++x)
      window.add(grid[y][x]);

    if (window.max() > max)
      max = window.max();
  }

  return max;
}

size_t vertical(Grid const &grid, size_t size)
{
  size_t max = 0;

  for (size_t x = 0; x != grid.size(); ++x)
  {
    Window window(size);

    for (size_t y = 0; y != grid.size(); ++y)
      window.add(grid[y][x]);

    if (window.max() > max)
      max = window.max();
  }

  return max;
}

size_t diagright(Grid const &grid, size_t size)
{
  size_t max = 0;
  size_t grid_size = grid.size();

  for (size_t y = 0; y != grid_size; ++y)
  {
    Window window(size);

    for (size_t s = 0; s + y != grid_size; ++s)
      window.add(grid[y + s][s]);

    if (window.max() > max)
      max = window.max();
  }

  for (size_t x = 1; x != grid_size; ++x)
  {
    Window window(size);

    for (size_t s = 0; s + x != grid_size; ++s)
      window.add(grid[s][x + s]);

    if (window.max() > max)
      max = window.max();
  }

  return max;
}

size_t diagleft(Grid const &grid, size_t size)
{
  size_t max = 0;
  size_t grid_size = grid.size();

  for (size_t y = 0; y != grid_size; ++y)
  {
    Window window(size);

    for (size_t s = 0; s <= y; ++s)
      window.add(grid[y - s][s]);

    if (window.max() > max)
      max = window.max();
  }

  // (x = 1, y = grid_size - 1)
  for (size_t x = 1; x != grid_size; ++x)
  {
    Window window(size);

    for (size_t s = 0; x + s < grid_size; ++s)
      window.add(grid[grid_size - 1 - s][x + s]);

    if (window.max() > max)
      max = window.max();
  }

  return max;
}

int main()
{
  size_t grid_size;
  size_t const window_size = 4;
  
  std::cin >> grid_size;
  
  Grid grid;
  grid.resize(grid_size, std::vector<size_t>(grid_size, 0));

  // Read stuff.
  for (size_t y = 0; y != grid_size; ++y)
    for (size_t x = 0; x != grid_size; ++x)
      std::cin >> grid[y][x];

  std::cout << horizontal(grid, window_size) << '\n';
  std::cout << vertical(grid, window_size) << '\n';
  std::cout << diagright(grid, window_size) << '\n';
  std::cout << diagleft(grid, window_size) << '\n';
}