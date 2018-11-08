#include <vector>
#include <iostream>
#include <limits>

size_t search(std::vector<size_t> &list, size_t n, size_t shortest = std::numeric_limits<size_t>::max(), size_t depth = 0)
{
    if (list[depth] == n) return depth;
    if (depth >= shortest) return shortest;

    for (int i = depth; i >= 0; --i)
    {
        size_t sum = list[i] + list[depth];
        if (sum > n) continue;
        if (sum == n) return depth + 1;
        list[depth + 1] = sum;
        shortest = search(list, n, shortest, depth + 1);
    }

    return shortest;
}

int main()
{
    std::vector<size_t> list(200, 1);
    size_t sum = 0;

    for (size_t i = 1; i <= 200; ++i)
        sum += search(list, i);

    std::cout << sum << '\n';
}