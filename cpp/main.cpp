#include <iostream>
#include <vector>
#include <unordered_set>
#include <iterator>
#include <cassert>
#include "graph.hpp"
#include "ordering.hpp"
int main(){
    std::vector<std::unordered_set<int>> adjacency(4);
    adjacency[0].insert({1,2,3});
    for (int i = 1; i < 4; i++){
        adjacency[i].insert(0);
    }
    Graph graph(adjacency);
    std::vector<int> ord = minimum_degree_ordering(graph);
    int res = evaluate_ordering(graph, ord);
    std::cout << res << '\n';
    for (int v : ord){
        std::cout << v << ' ';
    }
}