#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/breadth_first_search.hpp>
#include <boost/graph/named_function_params.hpp>
#include <boost/graph/visitors.hpp>
#include <boost/array.hpp>
#include <array>
#include <utility>
#include <algorithm>
#include <iostream>

using namespace boost;

// Example shows how breadth_first_search() is used with two visitors.
// To use two visitors, you need to put them in a pair with std::make_pair().
// If more than two visitors are needed, the pairs have to be nested.
int main()
{
  enum { topLeft, topRight, bottomRight, bottomLeft };

  std::array<std::pair<int, int>, 4> edges{{
    std::make_pair(topLeft, topRight),
    std::make_pair(topRight, bottomRight),
    std::make_pair(bottomRight, bottomLeft),
    std::make_pair(bottomLeft, topLeft)
  }};

  typedef adjacency_list<setS, vecS,
    undirectedS> graph;
  graph g{edges.begin(), edges.end(), 4};

  array<int, 4> distances{{0}};
  array<int, 4> predecessors;
  predecessors[bottomRight] = bottomRight;

  breadth_first_search(g, bottomRight,
    visitor(
      make_bfs_visitor(
        std::make_pair(
          record_distances(distances.begin(), on_tree_edge()),
          record_predecessors(predecessors.begin(), on_tree_edge())
        )
      )
    )
  );

  // std::copy(distances.begin(), distances.end(), 
  //    std::ostream_iterator<int>{std::cout, "\n"});
  std::for_each(distances.begin(), distances.end(),
    [](int d){ std::cout << d << '\n'; });

  int p = topLeft;
  while (p != bottomRight)
  {
    std::cout << p << '\n';
    p = predecessors[p];
  }
  std::cout << p << '\n';
}

