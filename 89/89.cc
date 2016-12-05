// #define CATCH_CONFIG_MAIN
// #include "../catch.hpp"
#include <string>
#include <iostream>

std::string toRoman(size_t number)
{
  std::string roman;

  // M
  roman.append(std::string(number / 1000, 'M'));
  number %= 1000;

  // CM
  if (number >= 900)
  {
    roman.append("CM");
    number -= 900;
  }

  // D
  if (number >= 500)
  {
    roman.push_back('D');
    number -= 500;
  }

  // CD
  if (number >= 400)
  {
    roman.append("CD");
    number -= 400;
  }

  // C
  roman.append(std::string(number / 100, 'C'));
  number %= 100;

  // XC
  if (number >= 90)
  {
    roman.append("XC");
    number -= 90;
  }

  // L
  if (number >= 50)
  {
    roman.push_back('L');
    number -= 50;
  }

  // XL
  if (number >= 40)
  {
    roman.append("XL");
    number -= 40;
  }

  // X
  roman.append(std::string(number / 10, 'X'));
  number %= 10;

  // IX
  if (number >= 9)
  {
    roman.append("IX");
    number -= 9;
  }
  
  // V
  if (number >= 5)
  {
    roman.push_back('V');
    number -= 5;
  }

  return roman.append(number == 4 ? "IV" : std::string(number, 'I'));
}

size_t toArabic(std::string const &roman)
{
  size_t num = 0;

  for(size_t idx = 0; idx < roman.size(); ++idx)
  {
    char next = idx + 1 < roman.size() ? roman[idx + 1] : ' ';
    switch(roman[idx])
    {
      case 'M':
        num += 1000;
      break;
      case 'D':
        num += 500;
      break;
      case 'C':
        if (next == 'M') {
          num += 900;
          ++idx;
          continue;
        }
        if (next == 'D') {
          num += 400;
          ++idx;
          continue;
        }
        num += 100;
      break;
      case 'L':
        num += 50;
      break;
      case 'X':
        if (next == 'C') {
          num += 90;
          ++idx;
          continue;
        }
        if (next == 'L') {
          num += 40;
          ++idx;
          continue;
        }
        num += 10;
      break;
      case 'V':
        num += 5;
      break;
      case 'I':
        if (next == 'X') {
          num += 9;
          ++idx;
          continue;
        }
        if (next == 'V') {
          num += 4;
          ++idx;
          continue;
        }
        ++num;
      break;
    }
  }

  return num;
}

int main()
{
  size_t saved = 0;

  std::string str;

  while (std::cin >> str)
  {
    std::string simplified(toRoman(toArabic(str)));

    saved += str.size() - simplified.size();
  }

  std::cout << saved << '\n';
}

// TEST_CASE("arabic_to_roman", "[roman]")
// {
//   REQUIRE(toRoman(1) == "I");
//   REQUIRE(toRoman(2) == "II");
//   REQUIRE(toRoman(3) == "III");
//   REQUIRE(toRoman(5) == "V");
//   REQUIRE(toRoman(10) == "X");
//   REQUIRE(toRoman(97) == "XCVII");
//   REQUIRE(toRoman(104) == "CIV");
//   REQUIRE(toRoman(106) == "CVI");
//   REQUIRE(toRoman(184) == "CLXXXIV");
//   REQUIRE(toRoman(1039) == "MXXXIX");
//   REQUIRE(toRoman(1250) == "MCCL");
//   REQUIRE(toRoman(1959) == "MCMLIX");
//   REQUIRE(toRoman(2999) == "MMCMXCIX");
// }

// TEST_CASE("roman_to_arabic", "[arabic]")
// {
//   REQUIRE(toArabic("I") == 1);
//   REQUIRE(toArabic("II") == 2);
//   REQUIRE(toArabic("III") == 3);
//   REQUIRE(toArabic("V") == 5);
//   REQUIRE(toArabic("X") == 10);
//   REQUIRE(toArabic("XCVII") == 97);
//   REQUIRE(toArabic("CIV") == 104);
//   REQUIRE(toArabic("CVI") == 106);
//   REQUIRE(toArabic("CLXXXIV") == 184);
//   REQUIRE(toArabic("MXXXIX") == 1039);
//   REQUIRE(toArabic("MCCL") == 1250);
//   REQUIRE(toArabic("MCMLIX") == 1959);
//   REQUIRE(toArabic("MMCMXCIX") == 2999);
// }