#include <boost/graph/adjacency_list.hpp>
#include <tuple>
#include <algorithm>
#include <iterator>
#include <iostream>

// It is possible to define a graph without calling boost::add_vertex().
// Boost.Graph adds missing points to a graph automatically if the points
// passed to boost::add_edge() don’t exist. 
//
// Dependency
// -std=c++11

int main()
{
  typedef boost::adjacency_list<boost::setS, boost::vecS, boost::undirectedS> graph;
  graph g;

  enum { topLeft, topRight, bottomRight, bottomLeft };

  boost::add_edge(topLeft, topRight, g);
  boost::add_edge(topRight, bottomRight, g);
  boost::add_edge(bottomRight, bottomLeft, g);
  boost::add_edge(bottomLeft, topLeft, g);

  std::cout << "print the vertices to verify the vertices are added automatically:" 
            << std::endl;
  graph::vertex_iterator vit, vend;
  std::tie(vit, vend) = boost::vertices(g);
  std::copy(vit, vend,
    std::ostream_iterator<graph::vertex_descriptor>(std::cout, "\n"));

  std::cout << "print the edges:"
            << std::endl;
  graph::edge_iterator eit, eend;
  std::tie(eit, eend) = boost::edges(g);
  std::copy(eit, eend,
    std::ostream_iterator<graph::edge_descriptor>(std::cout, "\n"));
}

