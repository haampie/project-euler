#include <iostream>

bool is_bouncy(size_t n)
{    
    bool up = false;
    bool down = false;
    
    size_t prevd = n % 10;
    n /= 10;

    while (n)
    {
        size_t next_d = n % 10;

        if (next_d > prevd) up = true;
        else if (next_d < prevd) down = true;
        if (up && down) return true;

        prevd = next_d;
        n /= 10;
    }

    return false;
}

int main()
{
    size_t bouncy = 0;

    for (size_t i = 1; i < 10'000'000; ++i)
    {
        if (is_bouncy(i))
            ++bouncy;
        
        if (100 * bouncy >= 99 * i)
        {
            std::cout << i << '\n';
            break;
        }
    }
}