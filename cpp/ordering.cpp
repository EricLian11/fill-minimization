#include "ordering.hpp"
#include "graph.hpp"
#include <vector>
#include <unordered_set>
#include <climits>
//Evaluate ordering implementation
int evaluate_ordering(Graph graph, const std::vector<int>& ord){
    int fc = 0;
    for (int v : ord){
        fc += graph.eliminate_vertex(v);
    }
    return fc;
}

//Minimum degree ordering implementation
std::vector<int> minimum_degree_ordering(Graph graph){
    /*
    idea: iterate through vertex degrees with Graph.degree, keep smallest.
    eliminate that vertex, repeat until all vertices are removed. 
    time complexity: O(V^3)
    */
    int total_active = graph.active_vertices().size();
    int removed = 0;
    int min_deg;
    int min_deg_v;
    int v_deg;
    
    std::vector<int> res(total_active);
    while (removed < total_active){
        min_deg = INT_MAX;
        min_deg_v = INT_MAX;
        for (int v : graph.active_vertices()){
            v_deg = graph.degree(v);
            if (v_deg < min_deg) {
                min_deg = v_deg;
                min_deg_v = v;
            }
            else if (v_deg == min_deg and v < min_deg_v) min_deg_v = v;
        }
        res[removed] = min_deg_v;
        graph.eliminate_vertex(min_deg_v);
        removed++;
    }
    return res;
}