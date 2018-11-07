#include <iostream>
#include <vector>
#include <algorithm>

size_t sum_of_digits(size_t n)
{
    size_t sum = 0;
    for (; n != 0; sum += n % 10, n /= 10);
    return sum;
}

int main()
{
    std::vector<size_t> list;

    for (size_t i = 2; i < 100; ++i)
    {
        for (size_t power = i; power < 1'000'000'000'000'000ull; power *= i)
        {
            if (power < 10) continue;
            size_t sum = sum_of_digits(power);
            if (sum == i) list.push_back(power);
        }
    }

    std::sort(list.begin(), list.end());

    for (size_t i = 0; i < list.size(); ++i)
        std::cout << i + 1 << ' ' << list[i] << '\n';
}