#include <iostream>
#include <vector>

template <class T> class Point2D
{
public:
  T const x;
  T const y;
  Point2D(T x, T y) : x(x), y(y)
  {}
};

template <class T>
std::ostream &operator<<(std::ostream &os, Point2D<T> const &point)
{
  return os << '(' << point.x << ',' << point.y << ')';
}

template <class T> class Polygon2D
{
  template <class X>
  friend std::ostream &operator<<(std::ostream &os, Polygon2D<X> const &poly);
  typename std::vector<Point2D<T>> vertices;

private:
  inline T is_left(Point2D<T> const &a, Point2D<T> const &b, Point2D<T> const &point) const
  {
    return (b.x - a.x) * (point.y - a.y)
           - (point.x -  a.x) * (b.y - a.y);
  }

public:
  Polygon2D()
  {}

  void add_point(Point2D<T> &&point)
  {
    vertices.emplace_back(point);
  }

  int winding_nr(Point2D<T> const &point) const
  {
    int wn = 0;

    for (size_t idx = 0; idx < vertices.size(); ++idx)
    {
      size_t next = (idx + 1) % vertices.size();

      if (vertices[idx].y <= point.y)
      {
        if (vertices[next].y > point.y && is_left(vertices[idx], vertices[next], point) > 0)
          ++wn;
        continue;
      }

      if (vertices[next].y <= point.y && is_left(vertices[idx], vertices[next], point) < 0)
        --wn;
    }

    return wn;
  }
};

template <class T>
std::ostream &operator<<(std::ostream &os, Polygon2D<T> const &poly)
{
  for (auto point : poly.vertices)
    os << point << ' ';

  return os;
}

int main()
{
  // Polygon2D<int> p;
  // p.add_point({ 1,  1});
  // p.add_point({ 1, -1});
  // p.add_point({-1, -2});
  // p.add_point({-3, -2});
  // p.add_point({-4, -1});
  // p.add_point({-3,  3});
  // p.add_point({-4,  2});
  // p.add_point({-5, -1});
  // p.add_point({-4, -3});
  // p.add_point({ 2, -4});
  // p.add_point({ 2,  2});
  // p.add_point({-2,  2});
  // p.add_point({-3,  0});
  // p.add_point({-2, -1});
  // p.add_point({-1,  0});
  // p.add_point({-1,  1});

  // p.add_point({-1,  1});
  // p.add_point({ 0, -1});
  // p.add_point({ 2,  1});
  // p.add_point({ 1,  3});
  // p.add_point({-1,  3});
  // p.add_point({-2,  1});
  // p.add_point({ 0, -2});
  // p.add_point({ 1,  1});
  // std::cout << p.winding_nr({0, 0}) << '\n';

  Point2D<int> origin{0, 0};
  size_t count = 0;

  while(std::cin.good())
  {
    Polygon2D<int> poly;
    for (size_t p = 1; p <= 3; ++p)
    {
      int x, y;
      std::cin >> x >> y;
      poly.add_point({x, y});
    }

    if (poly.winding_nr(origin) != 0)
      ++count;
  }

  std::cout << count << '\n';

}