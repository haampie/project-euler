#include <array>
#include <iostream>

template <class T>
size_t other_darts(T dart, T end, size_t sum, size_t left = 2)
{
    if (sum >= 100)
        return 0;

    size_t count = 1;

    if (left > 0)
        for (; dart != end; ++dart)
            count += other_darts(dart, end, sum + *dart, left - 1);

    return count;
}

size_t count()
{
    std::array<size_t, 62> scores{};
    std::array<size_t, 21> doubles{};

    for (size_t i = 1; i <= 20; ++i)
    {
        scores[3 * i - 3] = 1 * i;
        scores[3 * i - 2] = 2 * i;
        scores[3 * i - 1] = 3 * i;
        doubles[i - 1] = 2 * i;
    }

    scores[60] = 25;
    scores[61] = 50;
    doubles[20] = 50;

    size_t total = 0;
    
    for (size_t dart : doubles)
        total += other_darts(scores.begin(), scores.end(), dart);
    
    return total;
}

int main()
{
    std::cout << count() << '\n';
}