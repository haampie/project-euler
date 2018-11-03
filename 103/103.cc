#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <numeric>

// Sum of 2 is easy: just build a lookup table for sums -- disjoint = free.
template <class T>
bool is_two_sum(T begin, T end, std::vector<bool> &two_sum, size_t i)
{
    for (T p = begin; p != end; ++p)
        if (two_sum[*p + i])
            return true;

    return false;
}

// To check if {a,b,c,d,e,f,g} has two disjoint subsets e.g. {a,d,e} and {b,c,g} with equal
// sum we do a bit more work: list all the possible subsets of size 3 and then efficiently
// check if the remainder has a subset that sums to 3, using the fact that the list is
// sorted.
template<class T, class S>
bool has_three_sum(T begin, T end, S vbegin, S vend, int sum)
{
    T fixed = begin;
    S vfixed = vbegin;

    // Find a non-take value
    while (fixed != end && *fixed)
    {
        ++fixed;
        ++vfixed;

        T left = fixed + 1;
        S vleft = vfixed + 1;
        T right = end - 1;
        S vright = vend - 1;

        // Move left to a non-taken value
        while (left < right && *left)
        {
            ++left;
            ++vleft;
        }

        // Move right to a non-taken value
        while (left < right && *right)
        {
            --right;
            --vright;
        }

        while (left < right)
        {
            int sum2 = *vfixed + *vleft + *vright;

            if (sum2 == sum)
            {
                return true;
            }
            else if (sum2 > sum)
            {
                --right;
                --vright;

                // Move right to a non-taken value
                while (left < right && *right)
                {
                    --right;
                    --vright;
                }
            }
            else
            {
                ++left;
                ++vleft;

                // Move left to a non-taken value
                while (left < right && *left)
                {
                    ++left;
                    ++vleft;
                }
            }
        }
    }

    return false;
}

template<class T, class S>
bool _is_three_sum(T begin, T curr, T end, S vbegin, S vcurr, S vend, size_t remaining = 3, size_t sum = 0)
{
    if (remaining == 0)
        return has_three_sum(begin, end, vbegin, vend, sum);

    for (; curr < end - remaining + 1; ++curr, ++vcurr)
    {
        *curr = true;
        if (_is_three_sum(begin, curr + 1, end, vbegin, vcurr + 1, vend, remaining - 1, sum + *vcurr))
            return true;
        *curr = false;
    }

    return false;
}


// Checks whether 
template <class T>
bool is_three_sum(T begin, T end)
{
    std::vector<bool> marked(end - begin, false);

    return _is_three_sum(marked.begin(), marked.begin(), marked.end(), begin, begin, end);
}

template <class T>
bool run(T begin, T curr, T end, std::vector<bool> &two_sum)
{
    if (curr == end)
        return is_three_sum(begin, end);

    size_t n = curr - begin;
    size_t from = (begin == curr ? 1 : 1 + *(curr - 1));
    size_t to = 60;

    // Upper bound for *curr
    if (n >= 2) {
        to = std::accumulate(begin, begin + n / 2 + 1, 0) - std::accumulate(curr - n / 2 + 1, curr, 0);
    }
    
    for (size_t i = from; i < to; ++i)
    {
        // Verify not two-sum
        if (is_two_sum(begin, curr, two_sum, i))
            continue;

        // Mark two-sum
        for (T p = begin; p != curr; ++p)
            two_sum[*p + i] = true;
        
        // Set current number
        *curr = i;

        // Recurse
        if (run(begin, curr + 1, end, two_sum))
            return true;
        
        // Unmark two-sum
        for (T p = begin; p != curr; ++p)
            two_sum[*p + i] = false;
    }

    return false;
}

// run with ./103 7
int main(int argc, char ** argv)
{
    if (argc != 2)
    {
        std::cerr << "Provide one arg\n";
        return 1;
    }

    size_t n = std::stoul(argv[1]);
    std::vector<size_t> v(n, 0);
    std::vector<bool> sum(n * n * n, false);

    if (run(v.begin(), v.begin(), v.end(), sum))
    {
        std::ostream_iterator<size_t> it(std::cout, " ");
        std::copy(v.begin(), v.end(), it);
        std::cout << '\n';
    }
}