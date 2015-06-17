#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/named_function_params.hpp>
#include <boost/array.hpp>
#include <array>
#include <utility>
#include <iostream>

int main()
{
  enum { topLeft, topRight, bottomRight, bottomLeft };

  std::array<std::pair<int, int>, 5> edges{{
    std::make_pair(topLeft, topRight),
    std::make_pair(topRight, bottomRight),
    std::make_pair(bottomRight, bottomLeft),
    std::make_pair(bottomLeft, topLeft),
    std::make_pair(topLeft, bottomRight)
  }};

  struct edge_properties
  {
    int weight;
  };

  typedef boost::adjacency_list<boost::listS, boost::vecS,
    boost::undirectedS, boost::no_property,
    edge_properties> graph;

  /* alternatively

    graph g{edges.begin(), edges.end(), 4};

    graph::edge_iterator it, end;
    boost::tie(it, end) = boost::edges(g);
    g[*it].weight = 2;
    g[*++it].weight = 1;
    g[*++it].weight = 1;
    g[*++it].weight = 1;
    ...
  */
  boost::array<edge_properties, 5> props{{2, 1, 2, 2, 2}};

  /*
	template <class EdgeIterator, class EdgePropertyIterator>
	adjacency_list(EdgeIterator first, EdgeIterator last,
		       EdgePropertyIterator ep_iter,
		       vertices_size_type n,
		       vertices_size_type m = 0,
		       const GraphProperty& p = GraphProperty())
Creates a graph object with n vertices and with the edges specified in the edge list given by the range [first, last). The EdgeIterator and EdgePropertyIterator must be a model of InputIterator. The value type of the EdgeIterator must be a std::pair, where the type in the pair is an integer type. The integers will correspond to vertices, and they must all fall in the range of [0, n). The value_type of the ep_iter should be EdgeProperties.
*/
  graph g(edges.begin(), edges.end(), props.begin(), 4);

  // number of vertices
  boost::array<int, 4> directions;

  // weight_map make the function understand that weights are stored
  // in the weight variabe in edge_properties
  boost::dijkstra_shortest_paths(g, bottomRight,
    boost::predecessor_map(directions.begin()).
    weight_map(boost::get(&edge_properties::weight, g)));

  int p = topLeft;
  while (p != bottomRight)
  {
    std::cout << p << '\n';
    p = directions[p];
  }
  std::cout << p << '\n';
}
