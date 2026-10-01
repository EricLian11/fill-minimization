#include <vector>
#include <unordered_set>
#include "graph.hpp"
//Given a graph and an ordering, return the fill count
int evaluate_ordering(Graph graph, const std::vector<int>& ord);

//Minimum degree heuristic algorithm, returns ordering
std::vector<int> minimum_degree_ordering(Graph graph);
