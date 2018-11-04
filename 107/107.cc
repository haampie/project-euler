#include <vector>
#include <algorithm>
#include <numeric>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

class Connectivity
{
    // node i is root if parent[i] = i.
    std::vector<size_t> parent;

    // size[i] is the size of the subtree of node i
    std::vector<size_t> size;

public:
    explicit Connectivity(size_t n) : parent(n), size(n, 1)
    {
        std::iota(parent.begin(), parent.end(), 0);
    }

    void connect(size_t a, size_t b)
    {
        size_t ra = root(a);
        size_t rb = root(b);

        // Make the smaller tree a subtree of the larger
        if (size[ra] < size[rb])
        {
            parent[ra] = rb;
            size[rb] += size[ra];
        } else
        {
            parent[rb] = ra;
            size[ra] += size[rb];
        }
    }

    bool connected(size_t a, size_t b)
    {
        return root(a) == root(b);
    }

    inline bool is_root(size_t a)
    {
        return parent[a] == a;
    }

    size_t root(size_t a)
    {
        while (!is_root(a))
        {
            // Path compression: move current node further up the tree.
            parent[a] = parent[parent[a]];

            // Walk up the tree
            a = parent[a];
        }
        return a;
    }
};

struct Edge
{
    size_t from;
    size_t to;
    size_t weight;
    Edge(size_t from, size_t to, size_t weight) : from(from), to(to), weight(weight)
    {}
};

struct MinimalGraph
{
    size_t nodes;
    std::vector<Edge> edges;
};

size_t minspan(MinimalGraph &g)
{
    Connectivity c(g.nodes);

    std::sort(g.edges.begin(), g.edges.end(), [](Edge const &lhs, Edge const &rhs) {
        return lhs.weight < rhs.weight;
    });

    size_t min = 0;

    for (auto const &edge : g.edges) 
    {
        if (c.connected(edge.from, edge.to))
            continue;
        
        c.connect(edge.from, edge.to);
        min += edge.weight;
    }

    return min;
}

// Read graph from file
MinimalGraph construct_graph()
{
    std::ifstream csv("p107_network.txt");
    std::string line;

    MinimalGraph g{};

    for (size_t from = 0; std::getline(csv, line); ++from)
    {
        ++g.nodes;
        std::stringstream linestream(line);
        std::string value;

        for (size_t to = 0; std::getline(linestream, value, ','); ++to)
        {
            if (to <= from || value[0] == '-')
                continue;
            
            g.edges.emplace_back(from, to, std::stoul(value));
        }
    }

    return g;
}

int main()
{
    MinimalGraph g = construct_graph();
    size_t min = minspan(g);
    size_t max = std::accumulate(g.edges.begin(), g.edges.end(), 0, [](size_t sum, Edge const &rhs) {
        return sum + rhs.weight;
    });

    std::cout << "Saving = " << max - min << '\n';
}