#include <iostream>
#include <vector>
#include <unordered_set>
#include <iterator>
#include <cassert>
#include "graph.hpp"
#include "ordering.hpp"
#include "matrix_market.hpp"
#include <exception>
#include <chrono>

int main(int argc, char* argv[]){
    if (argc != 3){
        std::cerr << "Usage:fillmin <matrixpath> <heuristic>";
        return 1;
    }
        try {
    CoordinateMatrix cm = read_matrix_market(argv[1]);

    Graph graph = graph_from_matrix(cm);
    std::vector<int> ord;
    std::string heuristic = argv[2];
    auto start = std::chrono::steady_clock::now();
    if (heuristic == "md") {
        ord = minimum_degree_ordering(graph);

    }
    else if (heuristic == "mf") {
        ord = minimum_fillcost_ordering(graph);
    }
    
    else {
        std::cerr << "Invalid heuristic";
        return 1;
    }
    auto end = std::chrono::steady_clock::now();
    double elapsed_ms = std::chrono::duration<double, std::milli>(end - start).count();
    int res = evaluate_ordering(graph, ord);
    std::cout << elapsed_ms << '\n';
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