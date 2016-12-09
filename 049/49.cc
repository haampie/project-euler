#include <iostream>
#include <vector>

std::vector<bool> primes_below(size_t N)
{
  std::vector<bool> prime(N, true);

  for (size_t x = 3; x * x <= N; x += 2)
    if (prime[x])
      for (size_t m = x * x; m < N; m += 2 * x)
        prime[m] = false;

  return prime;
}

int main()
{
  const size_t cap = 10'000;
  auto prime = primes_below(cap);

  for (size_t fst = 1001; fst <= cap; fst += 2)
  {
    std::vector<char> count{0,0,0,0,0,0,0,0,0,0};
    ++count[fst % 10];
    ++count[(fst / 10) % 10];
    ++count[(fst / 100) % 10];
    ++count[fst / 1000];

    if ( !prime[fst])
      continue;
    
    for (size_t snd = fst + 2; snd <= cap; snd += 2)
    {
      if ( !prime[snd]) continue;
      std::vector<char> count2(count);
      if (count2[snd % 10] == 0) continue;
      --count2[snd % 10];
      if (count2[(snd / 10) % 10] == 0) continue;
      --count2[(snd / 10) % 10];
      if (count2[(snd / 100) % 10] == 0) continue;
      --count2[(snd / 100) % 10];
      if (count2[snd / 1000] == 0) continue;
      --count2[snd / 1000];

      size_t next = 2 * snd - fst;

      if (next >= 10'000)
        break;

      if (prime[next]) {
        std::vector<char> count3(count);
        if (count3[next % 10] == 0) continue;
        --count3[next % 10];
        if (count3[(next / 10) % 10] == 0) continue;
        --count3[(next / 10) % 10];
        if (count3[(next / 100) % 10] == 0) continue;
        --count3[(next / 100) % 10];
        if (count3[next / 1000] == 0) continue;
        --count3[next / 1000];
        std::cout << fst << ' ' << snd << ' ' << 2 * snd - fst << '\n';
      }

    }
  }
}