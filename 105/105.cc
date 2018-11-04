#include <vector>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <sstream>
#include <fstream>
#include <string>

template<class T>
bool _rule_1(T curr, T end, size_t left, size_t right, int sum = 0)
{
    // Just build all combinations of the form L.L..RLR.R: add L's, subtract R's,
    // if there are no L's and R's to be placed anymore, a zero sum indicates rule_1 is
    // violated. Assume left + right <= end - curr.
    if (left == 0 && right == 0)
        return sum != 0;

    // Make `curr` an `L`
    if (left != 0 && !_rule_1(curr + 1, end, left - 1, right, sum + *curr))
        return false;

    // Make `curr` a `.` only when the remained has enough space to put L's and R's
    if ((left + right < end - curr) && !_rule_1(curr + 1, end, left, right, sum))
        return false;

    // Make `curr` an `R`
    if (right != 0 && !_rule_1(curr + 1, end, left, right - 1, sum - *curr))
        return false;

    return true;
}

bool rule_1(std::vector<size_t> const &v)
{
    for (size_t len = 2; 2 * len <= v.size(); ++len)
        if (!_rule_1(v.begin(), v.end(), len, len))
            return false;

    return true;
}

bool rule_2(std::vector<size_t> const &v)
{
    if (v.size() < 3)
        return true;
    
    // Upper bound is minimal k-sum minus first k-2 elements of maximal (k-1)-sum.
    for (size_t idx = 2; idx < v.size(); ++idx)
        if (v[idx] >= std::accumulate(v.begin(), v.begin() + idx / 2 + 1, 0) - std::accumulate(v.begin() + idx - idx / 2 + 1, v.begin() + idx, 0))
            return false;

    return true;
}

// Reading from CSV file
std::vector<std::vector<size_t>> read_from_file()
{
    std::vector<std::vector<size_t>> values;

    std::ifstream csv("p105_sets.txt");
    std::string line;

    while (std::getline(csv, line))
    {
        std::stringstream lineStream(line);
        std::string value;

        std::vector<size_t> current_values;

        while (std::getline(lineStream, value, ','))
            current_values.push_back(std::stoul(value));

        std::sort(current_values.begin(), current_values.end());

        values.push_back(current_values);
    }

    return values;
}

int main()
{
    std::vector<std::vector<size_t>> values = read_from_file();
    size_t sum = 0;

    for (std::vector<size_t> &v : values)
        if (rule_2(v) && rule_1(v))
            sum += std::accumulate(v.begin(), v.end(), 0);

    std::cout << sum << '\n';
}