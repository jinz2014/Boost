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

  array<int, 4> pred{{0}};

  // define the start vertex
  int src = topLeft;

  breadth_first_search(g, src,
    visitor(
      // the visitor returned by make_bfs_visitor defines the member function tree_edge().
      // If a visitor that is defined with the tag boost::on_tree_edge is passed to 
      // boost::make_bfs_visitor() (as in Example 31.8), the visitor is notified when tree_edge() is called. 
      // This lets you use visitors with different algorithms without those visitors having 
      // to define all of the member functions expected by all algorithms.
      make_bfs_visitor(
        record_predecessors(pred.begin(), on_tree_edge()))));

  // After boost::breadth_first_search() returns, the property map predecessors 
  // contains the predecessor of every point. To find the first field when 
  // travelling from the top left to the bottom right, the element with the 
  // index 0 - the index of the top left field - is accessed in predecessors. 
  // The value found in predecessors is 1, which means the next field is at the top right.
  // Accessing predecessors with the index 1 returns the next field, which is the bottom 
  // right field - the one with the index 2. That way it’s possible to find the points 
  // iteratively in huge graphs to get from a start to an end point.
  int p = src;
  while (p != bottomRight)
  {
    std::cout << p << '\n';
    p = predecessors[p];
  }
  std::cout << p << '\n';
  
}


