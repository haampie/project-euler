#include <iostream>
#include <vector>
#include <iomanip>

enum Cells {
  GO, A1, CC1, A2, T1,
  R1, B1, CH1, B2, B3,
  JAIL, C1, U1, C2, C3,
  R2, D1, CC2, D2, D3,
  FP, E1, CH2, E2, E3,
  R3, F1, F2, U2, F3,
  G2J, G1, G2, CC3, G3,
  R4, CH3, H1, T2, H2
};

inline double chance_roll(size_t roll)
{
  if (roll <= 7)
    return static_cast<double>(roll - 1) / 36;

  return static_cast<double>(6 - (roll - 7)) / 36;
}

int main()
{
  size_t const total = 40;

  double jail_time = 5.0 / (6*6*6*6);
  double no_jail_time = 1 - jail_time;

  std::vector<std::vector<double>> chances(total, std::vector<double>(total, 0.0));

  for (size_t cell = 0; cell < total; ++cell)
  {
    chances[cell][JAIL] += jail_time;

    for (size_t roll = 2; roll < 13; ++roll)
    {
      size_t next = (cell + roll) % total;

      double chance = chance_roll(roll) * no_jail_time;

      switch (next)
      {
      case CC1:
      case CC2:
      case CC3:
        chances[cell][next] += chance * 7 / 8;
        chances[cell][GO] += chance / 16;
        chances[cell][JAIL] += chance / 16;
        break;
      case CH1:
        chances[cell][next] += chance * 3 / 8;
        chances[cell][GO] += chance / 16;
        chances[cell][JAIL] += chance / 16;
        chances[cell][C1] += chance / 16;
        chances[cell][E3] += chance / 16;
        chances[cell][H2] += chance / 16;
        chances[cell][R1] += chance / 16;
        chances[cell][R2] += chance * 2 / 16;
        chances[cell][U1] += chance / 16;
        chances[cell][next - 3] += chance / 16;
        break;
      case CH2:
        chances[cell][next] += chance * 3 / 8;
        chances[cell][GO] += chance / 16;
        chances[cell][JAIL] += chance / 16;
        chances[cell][C1] += chance / 16;
        chances[cell][E3] += chance / 16;
        chances[cell][H2] += chance / 16;
        chances[cell][R1] += chance / 16;
        chances[cell][R3] += chance * 2 / 16;
        chances[cell][U2] += chance / 16;
        chances[cell][next - 3] += chance / 16;
        break;
      case CH3:
        chances[cell][next] += chance * 3 / 8;
        chances[cell][GO] += chance / 16;
        chances[cell][JAIL] += chance / 16;
        chances[cell][C1] += chance / 16;
        chances[cell][E3] += chance / 16;
        chances[cell][H2] += chance / 16;
        chances[cell][R1] += chance * 3 / 16;
        chances[cell][U1] += chance / 16;
        chances[cell][next - 3] += chance / 16;
        break;
      case G2J:
        chances[cell][JAIL] += chance;
        break;
      default:
        chances[cell][next] += chance;
        break;
      }
    }
  }

  for (size_t from = 0; from != total; ++from)
  {
    if (from == G2J)
      continue;

    for (size_t to = 0; to != total; ++to)
    {
      if (to == G2J)
        continue;

      std::cout << std::setprecision(10) << std::setw(16) << chances[from][to] << ' ';
    }

    std::cout << '\n';
  }
}