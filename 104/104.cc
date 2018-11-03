#include <vector>
#include <iostream>
#include <iterator>

// base 10
class UnsignedBigNum
{
    std::vector<uint8_t> _digits;

    friend std::ostream &operator<<(std::ostream &, UnsignedBigNum const&);

public:
    explicit UnsignedBigNum(uint8_t v) : _digits{v}
    {}

    UnsignedBigNum &operator+=(UnsignedBigNum const &rhs)
    {
        if (_digits.size() < rhs._digits.size())
            _digits.resize(rhs._digits.size(), 0);
        
        for (size_t idx = 0; idx < rhs._digits.size(); ++idx)
            _digits[idx] += rhs._digits[idx];

        overflow();

        return *this;
    }

    std::vector<uint8_t> const &digits() const
    {
        return _digits;
    }

private:
    void overflow()
    {
        for (size_t idx = 0; idx < _digits.size(); ++idx)
        {
            if (_digits[idx] >= 10)
            {
                auto d = _digits[idx] / 10;
                _digits[idx] %= 10;

                if (idx + 1 == _digits.size())
                    _digits.push_back(d);
                else
                    _digits[idx + 1] += d;
            }
        }
    }
};

std::ostream &operator<<(std::ostream &os, UnsignedBigNum const &bn)
{
    std::copy(bn._digits.rbegin(), bn._digits.rend(), std::ostream_iterator<size_t>(os, ""));
    return os;
}

template<class T>
bool is_pandigit(T begin, T end)
{
    if (end - begin < 9)
        return false;

    std::vector<bool> table(10, false);

    for (T p = begin; p != begin + 9; ++p)
    {
        if (*p == 0 || table[*p])
            return false;
        
        table[*p] = true;
    }

    return true;
}

int main()
{
    UnsignedBigNum prev(0);
    UnsignedBigNum curr(1);

    // found 329468 after running it for a while
    for (size_t n = 2; n <= 329'468; ++n)
    {
        auto tmp = curr;
        curr += prev;
        prev = tmp;

        std::vector<uint8_t> const &digits = curr.digits();
        auto front = is_pandigit(digits.begin(), digits.end());
        auto back = is_pandigit(digits.rbegin(), digits.rend());

        if (front && back)
        {
            std::cout << n << '(' << digits.size() <<  " digits):\n" << curr << '\n';
            break;
        }
    }
}