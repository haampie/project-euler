#include <iostream>
#include <array>

using Board = std::array<std::array<uint8_t, 9>, 9>;

class Solver {
  friend std::ostream &operator<<(std::ostream &os, Solver solver);

  struct Coord {
    uint8_t const x;
    uint8_t const y;
    uint8_t const z;
    Coord(uint8_t x, uint8_t y) 
    : x(x), y(y), z(3 * (y / 3) + x / 3)
    {}
  };

  Board board;
  std::array<std::array<bool, 10>, 9> row;
  std::array<std::array<bool, 10>, 9> column;
  std::array<std::array<bool, 10>, 9> box;

  Coord next(Coord const &coord) const
  {
    Coord test = [&coord]() -> Coord {
      if (coord.x + 1 == 9)
        return Coord(0, coord.y + 1);

      return Coord(coord.x + 1, coord.y);
    }();

    if (test.y != 9 && board[test.y][test.x] != 0)
      return next(test);

    return test;
  }

  bool bruteforce(Coord coord)
  {
    // Solved!
    if (coord.x == 0 && coord.y == 9)
      return true;

    for (uint8_t num = 1; num < 10; ++num)
    {
      if (row[coord.y][num] && column[coord.x][num] && box[coord.z][num])
      {
        // Occupy square
        row[coord.y][num] = column[coord.x][num] = box[coord.z][num] = false;
        board[coord.y][coord.x] = num;

        // If this solves it, then return :)
        if (bruteforce(next(coord)))
          return true;

        // Undo last move
        board[coord.y][coord.x] = 0;
        row[coord.y][num] = column[coord.x][num] = box[coord.z][num] = true;
      }
    }

    return false;
  }

public:

  Solver()
  {
    for (auto &row : board)
      row.fill(0);
    
    for (auto &nums : row)
      nums.fill(true);
    
    for (auto &nums : column)
      nums.fill(true);

    for (auto &nums : box)
      nums.fill(true);
  }

  Solver(Board const &copy) : board(copy)
  {
    for (auto &nums : row)
      nums.fill(true);
    
    for (auto &nums : column)
      nums.fill(true);

    for (auto &nums : box)
      nums.fill(true);

    for (uint8_t y = 0; y != 9; ++y)
      for (uint8_t x = 0; x != 9; ++x)
        if (board[y][x] != 0)
        {
          row[y][board[y][x]] = false;
          column[x][board[y][x]] = false;
          box[Coord(x, y).z][board[y][x]] = false;
        }
  }

  void solve()
  {
    if (board[0][0] != 0)
      bruteforce(next({0, 0}));

    bruteforce({0, 0});
  }

  inline size_t sum_of_top_left() const
  {
    return 100 * static_cast<size_t>(board[0][0]) 
      + 10 * static_cast<size_t>(board[0][1]) 
      + static_cast<size_t>(board[0][2]);
  }
};

std::ostream &operator<<(std::ostream &os, Solver solver)
{
  for (auto const &row : solver.board)
  {
    for (auto num : row)
      os << static_cast<uint16_t>(num) << ' ';

    os << '\n';
  }

  return os;
}

int main()
{
  size_t sum = 0;

  while(std::cin.good())
  {
    Board board;

    for (uint8_t y = 0; y != 9; ++y)
    {
      for (uint8_t x = 0; x != 9; ++x)
      {
        size_t num;
        std::cin >> num;
        board[y][x] = num;
      }
    }

    Solver solver(board);
    solver.solve();
    sum += solver.sum_of_top_left();
    // std::cout << solver;
  }

  std::cout << "Sum = " << sum << '\n';
}