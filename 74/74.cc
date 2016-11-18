#include <iostream>
#include <vector>

class Graph {
  struct Node {
    size_t distance;
    size_t next;
    Node() : distance(0), next(0) {}
  };
  
  size_t factorial[10] {
    1, 1, 2, 6, 24, 120, 720, 5'040, 40'320, 362'880
  };

  size_t max;
  std::vector<Node> graph;

public:
  Graph(size_t max)
    : max(max), graph(3'265'921)
  {}

  size_t total_of_length(size_t length)
  {
    size_t total = 0;

    for (size_t num = 0; num != max; ++num)
      if (length_of(num) == length)
        ++total;

    return total;
  }

private:
  size_t next(size_t num) const
  {
    if (num == 0)
      return 1;

    size_t sum = 0;

    for (; num != 0; num /= 10)
      sum += factorial[num % 10];

    return sum;
  }

  size_t length_of(size_t num)
  {
    if (graph[num].next != 0)
      return graph[num].distance;

    graph[num].next = next(num);
    return graph[num].distance = 1 + length_of(graph[num].next);
  }
};

int main()
{
  Graph graph(1'000'000);
  std::cout << graph.total_of_length(60) << '\n';
}