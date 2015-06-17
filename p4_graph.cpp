#include <boost/graph/adjacency_list.hpp>
#include <utility>
#include <algorithm>
#include <iterator>
#include <iostream>

// specify the adjacency_list object with predefined parameters
//
// Simulation results:
//
// for directed and bidirectional graph, the outputs are the same:
// true, false, true, (0,1), (1,0)
// for undirected graph, the outputs are:
// true, false, false, (0,1)

int main()
{
  // 
  // set for edges and vector for vertices
  //typedef boost::adjacency_list<boost::setS, boost::vecS, boost::undirectedS> graph;
  //typedef boost::adjacency_list<boost::setS, boost::vecS, boost::directedS> graph;
  typedef boost::adjacency_list<boost::setS, boost::vecS, boost::bidirectionalS> graph;
  graph g;

  boost::adjacency_list<>::vertex_descriptor v1 = boost::add_vertex(g);
  boost::adjacency_list<>::vertex_descriptor v2 = boost::add_vertex(g);
  boost::add_vertex(g);
  boost::add_vertex(g);

  std::pair<graph::edge_descriptor, bool> p =
    boost::add_edge(v1, v2, g);
  std::cout.setf(std::ios::boolalpha);
  std::cout << p.second << '\n';

  // duplicate
  p = boost::add_edge(v1, v2, g);
  std::cout << p.second << '\n';

  // The third call to the function boost::add_edge() swaps
  // the start and end points, but because lines in this example
  // are undirected, this line is the same as the previous lines 
  // and, therefore, isn't added.
  p = boost::add_edge(v2, v1, g);
  std::cout << p.second << '\n';

  std::pair<graph::edge_iterator,
    graph::edge_iterator> es = boost::edges(g);

  std::copy(es.first, es.second,
    std::ostream_iterator<graph::edge_descriptor>(std::cout, "\n"));
}

