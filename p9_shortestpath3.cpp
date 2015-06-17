#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/named_function_params.hpp>
#include <boost/array.hpp>
#include <array>
#include <utility>
#include <iostream>

//using namespace boost;

int main()
{
  enum {A, B, C, D, E};
  char name[] = "ABCDE";

  std::array<std::pair<int, int>, 9> edges({
    std::make_pair(A, C),
    std::make_pair(B, B),
    std::make_pair(B, D),
    std::make_pair(B, E),
    std::make_pair(C, B),
    std::make_pair(C, D),
    std::make_pair(D, E),
    std::make_pair(E, A),
    std::make_pair(E, B)
  });

  /* edge_array.begin()/end() is not supported
  typedef std::pair<int, int> Edge;
  Edge edge_array[] = {
    Edge(A,C),
    Edge(B,C)
  };
  graph g(edge_array.begin(), edge_array.end(), props.begin(), 5);
  */

  struct edge_properties {
    int weight;
  };

  boost::array<edge_properties, 9> props({1, 2, 1, 2, 7, 3, 1, 1, 1});

  typedef boost::adjacency_list<boost::listS, boost::vecS,
    boost::directedS, 
    boost::no_property,
    edge_properties> graph;

  //  initialize user-defined properties when a graph is defined. 
  graph g(edges.begin(), edges.end(), props.begin(), 5);

  boost::array<int, 5> direction;
  boost::array<int, 5> distance;

  // weight_map make the function understand that weights are stored
  // in the weight variable in edge_properties
  boost::dijkstra_shortest_paths(g, A,
    boost::predecessor_map(direction.begin())
    .distance_map(distance.begin())
    .weight_map(boost::get(&edge_properties::weight, g)));

  graph::vertex_iterator vi, vend;
  for (std::tie(vi, vend) = vertices(g); vi != vend; vi++) {
    std::cout << "distance(" << name[*vi] << ") = " 
               << distance[*vi] << ", ";
    std::cout << "parent(" << name[*vi] << ") = " 
               << name[direction[*vi]] << '\n'; 
  };
}
