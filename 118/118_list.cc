#include <array>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

struct IsPrime
{
    std::vector<size_t> testers;

    IsPrime(size_t n) : testers()
    {
        // Generate test primes
        std::vector<bool> prime(n, true);

        for (size_t x = 3; x * x <= n; x += 2)
            if (prime[x])
                for (size_t m = x * x; m < n; m += 2 * x)
                    prime[m] = false;

        testers.push_back(2);

        for (size_t x = 3; x < n; x += 2)
            if (prime[x])
                testers.push_back(x);
    }

    bool operator()(size_t candidate) const
    {
        if (candidate <= 1)
            return false;

        for (auto p : testers)
        {
            if (p * p > candidate)
                return true;

            if (candidate % p == 0)
                return false;
        }
        
        return true;
    }
};

template <class T>
void partitioned_pandigit(IsPrime const &is_prime, std::vector<size_t> &stack, T current, T end, size_t max_first_digit = 0, size_t number = 0)
{
    if (current == end)
    {
        if (number == 0)
        {
            std::copy(stack.begin(), stack.end(), std::ostream_iterator<size_t>(std::cout, " "));
            std::cout << '\n';
        }

        return;
    }

    for (T digit = current; digit != end; ++digit)
    {
        // If we construct the first digit of the next prime number make sure the digit 
        // exceeds the first digit of the previous prime number.
        if (number == 0 && *digit < max_first_digit)
            continue;

        // Move the digit to the current position
        std::iter_swap(current, digit);

        // If we start constructing a new prime number we have to update the max_first_digit
        size_t first_digit = number == 0 ? *current : max_first_digit;

        // Append the next digit
        size_t candidate = 10 * number + *current;

        // If this number is prime, then we can start a new group
        if (is_prime(candidate))
        {
            stack.push_back(candidate);
            partitioned_pandigit(is_prime, stack, current + 1, end, first_digit, 0);
            stack.pop_back();
        }

        // In any case we can try to add more digits.
        partitioned_pandigit(is_prime, stack, current + 1, end, first_digit, candidate);

        // Put the number back where it came from.
        std::iter_swap(current, digit);
    }
}

int main()
{
    std::array<size_t, 9> v{1,2,3,4,5,6,7,8,9};
    std::vector<size_t> stack{};
    IsPrime is_prime(31'622);
    partitioned_pandigit(is_prime, stack, v.begin(), v.end());
}