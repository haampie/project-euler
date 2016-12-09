#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> names_base = {
  "",
  "one",
  "two",
  "three",
  "four",
  "five",
  "six",
  "seven",
  "eight",
  "nine",
  "ten",
  "eleven",
  "twelve",
  "thirteen",
  "fourteen",
  "fifteen",
  "sixteen",
  "seventeen",
  "eighteen",
  "nineteen"
};

std::vector<std::string> names_tens = {
  "",
  "",
  "twenty",
  "thirty",
  "forty",
  "fifty",
  "sixty",
  "seventy",
  "eighty",
  "ninety"
};

std::string toString(size_t N)
{
  size_t hundreds = N / 100;
  N -= 100 * hundreds;

  std::string text = "";

  if (hundreds > 0 && hundreds < names_base.size()) {
    text += names_base[hundreds];
    text += " hundred";

    if (N > 0) {
      text += " and ";
    }
  }

  if (N < 20) {
    text += names_base[N];
  } else {
    size_t tens = N / 10;
    N -= 10 * tens;

    text += names_tens[tens];

    if (N > 0) {
      text += "-";
      text += names_base[N];
    }
  }

  return text;
}

size_t num_chars(std::string const &word)
{
  size_t count = 0;

  for (auto it = word.begin(); it != word.end(); ++it)
    if (*it >= 'a' && *it <= 'z')
      ++count;

  return count;
}

int main()
{

  std::cout << num_chars(toString(115)) << '\n';

  // one thousand
  size_t total = 3 + 8;

  for (size_t num = 1; num != 1000; ++num)
  {
    std::string word = toString(num);
    total += num_chars(word);
    std::cout << word << '\n';
  }

  // std::cout << "one thousand\n";

  std::cout << "Total chars = " << total << '\n';
}