#include <iostream>
#include <queue>
#include <algorithm>
#include <iterator>
#include <functional>

class DiGraph {
  class Edge {
    size_t d_to;
    size_t d_weight;
  public:
    Edge(size_t to, size_t weight)
    : d_to(to), d_weight(weight)
    {}

    inline size_t to() const
    {
      return d_to;
    }

    inline size_t weight() const
    {
      return d_weight;
    }
  };

  std::vector<std::vector<Edge>> edges;

public:
  DiGraph(size_t vertices)
  {
    edges.resize(vertices);
  }

  void add_edge(size_t from, size_t to, size_t weight)
  {
    edges[from].emplace_back(to, weight);
  }

  std::vector<Edge> neighbours(size_t node) const
  {
    return std::vector<Edge>(
      edges[node].begin(),
      edges[node].end()
    );
  }

  inline size_t size() const
  {
    return edges.size();
  }
};

struct SearchNode {
  size_t vertex;
  size_t distance;
  SearchNode(size_t vertex, size_t distance)
  : vertex(vertex), distance(distance)
  {}

  bool operator>(SearchNode const &rhs) const
  {
    return distance > rhs.distance;
  }
};

size_t shortest_path(DiGraph const &graph, size_t from, size_t goal)
{
  std::vector<SearchNode> queue{{from, 0}};
  std::vector<size_t> path(graph.size(), graph.size());

  while (! queue.empty())
  {
    size_t current_vertex = queue[0].vertex;

    if (current_vertex == goal)
      break;

    for (auto edge : graph.neighbours(current_vertex))
    {
      size_t distance = queue[0].distance + edge.weight();

      if (path[edge.to()] == graph.size())
      {
        path[edge.to()] = current_vertex;
        queue.emplace_back(edge.to(), distance);
        std::push_heap(queue.begin(), queue.end(), std::greater<>{});
        continue;
      }

      // Search the neighbour in the queue
      for (size_t idx = 0; idx != queue.size(); ++idx)
      {
        if (queue[idx].vertex == edge.to())
        {
          // Maybe update its distance.
          if (queue[idx].distance > distance)
          {
            queue[idx].distance = distance;
            path[edge.to()] = current_vertex;
            std::make_heap(queue.begin(), queue.end(), std::greater<>{});
          }

          break;
        }
      }
    }

    std::pop_heap(queue.begin(), queue.end(), std::greater<>{});
    queue.pop_back();
  }

  return queue[0].distance;
}

inline size_t id(size_t x, size_t y, size_t N)
{
  return y * N + x;
}

int main()
{
  size_t N = *std::istream_iterator<size_t>(std::cin);

  std::vector<std::vector<size_t>> square;

  // Read all weights.
  for (size_t y = 0; y != N; ++y)
  {
    square.push_back(std::vector<size_t>());

    std::copy_n(
      std::istream_iterator<size_t>(std::cin),
      N,
      std::back_inserter(square[y])
    );
  }

  // Construct graph.
  size_t const source = N * N;
  size_t const sink = N * N + 1;
  DiGraph graph(N * N + 2);

  // Horizontal
  for (size_t y = 0; y != N; ++y)
    for (size_t x = 1; x != N; ++x)
      graph.add_edge(id(x - 1, y, N), id(x, y, N), square[y][x]);

  // Vertical
  for (size_t y = 1; y != N; ++y)
  {
    for (size_t x = 0; x != N; ++x)
    {
      graph.add_edge(id(x, y - 1, N), id(x, y, N), square[y][x]);
      graph.add_edge(id(x, y, N), id(x, y - 1, N), square[y - 1][x]);
    }
  }

  // Source and sink resp.
  for (size_t y = 0; y != N; ++y)
  {
    graph.add_edge(source, id(0, y, N), square[y][0]);
    graph.add_edge(id(N - 1, y, N), sink, 0);
  }

  std::cout << shortest_path(graph, source, sink) << '\n';
}