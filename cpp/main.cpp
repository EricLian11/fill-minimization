#include <iostream>
#include <vector>
#include <unordered_set>
#include <iterator>
#include <cassert>
#include "graph.hpp"
#include "ordering.hpp"
#include "matrix_market.hpp"
#include <exception>
int main(int argc, char* argv[]){
    if (argc != 2){
        std::cerr << "Usage:fillmin <matrixpath>";
        return 1;
    }
        try {
    CoordinateMatrix cm = read_matrix_market(argv[1]);

    Graph graph = graph_from_matrix(cm);
    std::vector<int> ord = minimum_degree_ordering(graph);
    int res = evaluate_ordering(graph, ord);
    std::cout << res << '\n';
    for (int v : ord){
        std::cout << v << ' ';
    }
            }

    catch (const std::exception& e){
        std::cerr << e.what() << '\n';
        return 1;
    }
}