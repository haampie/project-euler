#include <iostream>
#include <string>
#include <algorithm>

inline size_t cube(size_t n) {
  return n * n * n;
}

struct Cube {
  size_t sorted;
  size_t original;

  Cube(size_t n) : original(n) {
    auto str = std::to_string(cube(n));
    std::sort(str.begin(), str.end());
    sorted = std::stoull(str);
  }
};

int main()
{
  std::vector<Cube> nums;

  for (size_t n = 2154; n != 10000; ++n) {
    nums.emplace_back(n);
  }

  std::sort(nums.begin(), nums.end(), [](Cube const &a, Cube const &b) {
    return a.sorted > b.sorted; 
  });

  for (size_t idx = 0; idx < nums.size(); ++idx)
    for (size_t l = 1; idx + 1 < nums.size() && nums[idx].sorted == nums[idx + 1].sorted; ++idx, ++l)
      if (l == 4)
      {
        std::cout << nums[idx + 1].original << ' ' << cube(nums[idx + 1].original) << ' ' << nums[idx + 1].sorted << '\n';
        std::cout << nums[idx].original << ' ' << cube(nums[idx].original) << ' ' << nums[idx].sorted << '\n';
        std::cout << nums[idx - 1].original << ' ' << cube(nums[idx - 1].original) << ' ' << nums[idx - 1].sorted << '\n';
        std::cout << nums[idx - 2].original << ' ' << cube(nums[idx - 2].original) << ' ' << nums[idx - 2].sorted << '\n';
        std::cout << nums[idx - 3].original << ' ' << cube(nums[idx - 3].original) << ' ' << nums[idx - 3].sorted << '\n' << '\n';
      }


}