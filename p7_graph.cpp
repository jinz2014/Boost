// illustrates how to define a graph with adjacency_list 
// without having to call add_edge() for every line.
//
// You can pass iterators to the constructor of adjacency_list that refer to objects of type std::pair<int, int>, which define lines. If you pass iterators, you also have to supply a third parameter that determines the total number of points in the graph. The graph will contain at least the points required for the lines. The third parameter let’s you add points to the graph that aren’t connected to other points.

// Example 31.7 uses the functions num_vertices() and num_edges(), which return the number of points and lines, respectively. The example displays 4 twice.

// Example 31.7 calls adjacency_list::clear(). This member function removes all points and lines. It is a member function of adjacency_list and not a free-standing function.
//


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


int main()
{
  enum { topLeft, topRight, bottomRight, bottomLeft };

  std::array<std::pair<int, int>, 4> edges({
    std::make_pair(topLeft, topRight),
    std::make_pair(topRight, bottomRight),
    std::make_pair(bottomRight, bottomLeft),
    std::make_pair(bottomLeft, topLeft)
  });


  typedef boost::adjacency_list<boost::setS, boost::vecS,
    boost::undirectedS> graph;
  graph g(edges.begin(), edges.end(), 4);

  std::cout << boost::num_vertices(g) << '\n';
  std::cout << boost::num_edges(g) << '\n';

  boost::array<int, 4> distances({0,0,0,0});

  boost::breadth_first_search(g, topLeft,
    boost::visitor(
      boost::make_bfs_visitor(
        boost::record_distances(distances.begin(),
          boost::on_tree_edge{}))));

  std::copy(distances.begin(), distances.end(),
    std::ostream_iterator<int>(std::cout, "\n"));

  g.clear();
}

