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

  std::array<std::pair<int, int>, 4> edges{{
    std::make_pair(topLeft, topRight),
    std::make_pair(topRight, bottomRight),
    std::make_pair(bottomRight, bottomLeft),
    std::make_pair(bottomLeft, topLeft)
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
  */
  boost::array<edge_properties, 4> props{{2, 1, 1, 1}};

  //  initialize user-defined properties when a graph is defined. 
  graph g{edges.begin(), edges.end(), props.begin(), 4};

  boost::array<int, 4> directions;
  boost::array<int, 4> distance;

  // weight_map make the function understand that weights are stored
  // in the weight variabe in edge_properties
  boost::dijkstra_shortest_paths(g, bottomRight,
    boost::predecessor_map(directions.begin())
    .distance_map(distance.begin())
    .weight_map(boost::get(&edge_properties::weight, g)));

  int p = topLeft;
  while (p != bottomRight) {
    std::cout << p << " " << distance[p] << '\n';
    p = directions[p];
  }
  std::cout << p << " " << distance[p] << '\n';
}
