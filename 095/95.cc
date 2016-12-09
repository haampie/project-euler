#include <iostream>
#include <vector>
#include <chrono>

using it = std::vector<size_t>::const_iterator;

std::vector<size_t> primes_below(size_t N)
{
  std::vector<bool> prime(N, true);

  for (size_t x = 3; x * x <= N; x += 2)
    if (prime[x])
      for (size_t m = x * x; m < N; m += 2 * x)
        prime[m] = false;

  std::vector<size_t> primes;

  primes.push_back(2);

  for (size_t x = 3; x < N; x += 2)
    if (prime[x])
      primes.push_back(x);

  return primes;
}

void construct_numbers(it current, it last, size_t product, size_t sum, size_t const N, std::vector<size_t> &edges)
{

  // Sum of proper divisors is too large
  if (sum > N + product)
    return;

  // Last prime factor or too large number.
  if (current == last || product * (*current) > N)
  {
    edges[product] = sum - product;
    return;
  }

  // Multiply by prime factor as long as product <= N
  for (size_t sum_factor = 1, multiplier = 1; product <= N; product *= *current)
  {
    construct_numbers(current + 1, last, product, sum_factor * sum, N, edges);
    multiplier *= *current;
    sum_factor += multiplier;
  }
}

enum Node {UNMARKED, MARKED, INVALID, CYCLE};

size_t smallest_element_of_longest_chain(std::vector<size_t> const &edges)
{
  size_t min_element = 0;
  size_t longest = 0;

  std::vector<Node> nodes(edges.size(), UNMARKED);

  for (size_t idx = 1; idx < edges.size(); ++idx)
  {
    // Already visited this node.
    if (nodes[idx] != UNMARKED)
      continue;

    // Explore the current path
    size_t tail = idx;
    do
    {
      nodes[tail] = MARKED;
      tail = edges[tail];
    } while (nodes[tail] == UNMARKED);

    // Mark the non-cycle part as invalid
    for (size_t node = idx; node != tail; node = edges[node])
      nodes[node] = INVALID;

    // Reached an existing cycle? Then we're done
    if (nodes[tail] == CYCLE || nodes[tail] == INVALID)
      continue;

    // Otherwise we've found a new cycle
    size_t curr_min = tail;
    size_t length = 1;
    nodes[tail] = CYCLE;

    for (size_t node = edges[tail]; node != tail; node = edges[node])
    {
      ++length;
      nodes[node] = CYCLE;
      if (node < curr_min)
        curr_min = node;
    }

    // Longer than previous cycle?
    if (length > longest)
    {
      longest = length;
      min_element = curr_min;
    }
  }

  return min_element;
}

int main()
{
  size_t const N = 1'000'000;

  // STAGE 1: Find prime numbers
  auto t1 = std::chrono::high_resolution_clock::now();
  auto primes = primes_below(N);

  // STAGE 2: Find edges (i.e. sum of divisors)
  auto t2 = std::chrono::high_resolution_clock::now();
  std::vector<size_t> edges(N + 1, 0);
  construct_numbers(primes.begin(), primes.end(), 1, 1, N, edges);

  // STAGE 3: Compute longest chain
  auto t3 = std::chrono::high_resolution_clock::now();
  size_t min_el = smallest_element_of_longest_chain(edges);  

  // DONE
  auto t4 = std::chrono::high_resolution_clock::now();

  std::cout << "Primes: " << std::chrono::duration<double, std::milli>(t2 - t1).count() << '\n'
            << "Edges: " << std::chrono::duration<double, std::milli>(t3 - t2).count() << '\n'
            << "Chain: " << std::chrono::duration<double, std::milli>(t4 - t3).count() << '\n';

  std::cout << min_el << '\n';
}