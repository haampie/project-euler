#include <iostream>
#include <vector>
#include <string>

bool leap_year(size_t year)
{
  return year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
}

int main()
{
  size_t year = 1900;
  size_t month = 1;
  size_t days_passed = 0;
  size_t sundays = 0;

  std::vector<std::string> names = {"maandag", "dinsdag", 
  "woensdag", "donderdag", "vrijdag", "zaterdag", "zondag"};

  std::vector<size_t> month_length = {0, 
    31, 28, 31, 30, 31, 30, 
    31, 31, 30, 31, 30, 31
  };
  
  while (year < 2001)
  {
    days_passed += month_length[month];

    if (month == 2 && leap_year(year))
      ++days_passed;


    ++month;

    if (month > 12) {
      month = 1;
      ++year;
    }

    if (year >= 1901 && year <= 2000 && days_passed % 7 == 6)
      ++sundays;

    std::cout << '(' << year << ", " << month << ", 1): " 
      << days_passed << ' ' << names[days_passed % 7] << '\n';
  }

  std::cout << sundays << '\n';
}