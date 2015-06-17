#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/breadth_first_search.hpp>
#include <boost/graph/named_function_params.hpp>
#include <boost/graph/visitors.hpp>
#include <boost/array.hpp>
#include <array>
#include <utility>
#include <iterator>
#include <algorithm>
#include <iostream>

using namespace boost;

int main()
{
  enum { topLeft, topRight, bottomRight, bottomLeft };

  std::array<std::pair<int, int>, 4> edges{{
    std::make_pair(topLeft, topRight),
    std::make_pair(topRight, bottomRight),
    std::make_pair(bottomRight, bottomLeft),
    std::make_pair(bottomLeft, topLeft)
  }};

  typedef adjacency_list<setS, vecS, undirectedS> graph;
  graph g{edges.begin(), edges.end(), 4};

  array<int, 4> distances{{0}};

  breadth_first_search(g, topLeft,
    visitor(
      // the visitor returned by make_bfs_visitor defines the member function tree_edge().
      // If a visitor that is defined with the tag boost::on_tree_edge is passed to 
      // boost::make_bfs_visitor() (as in Example 31.8), the visitor is notified when tree_edge() is called. 
      // This lets you use visitors with different algorithms without those visitors having 
      // to define all of the member functions expected by all algorithms.
      make_bfs_visitor(
        record_distances(distances.begin(), on_tree_edge()))));

  std::copy(distances.begin(), distances.end(),
    std::ostream_iterator<int>{std::cout, "\n"});
}

