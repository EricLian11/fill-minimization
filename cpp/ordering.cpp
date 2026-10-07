#include "ordering.hpp"
#include "graph.hpp"
#include <vector>
#include <unordered_set>
#include <climits>
#include <utility>
//Evaluate ordering implementation
int evaluate_ordering(Graph graph, const std::vector<int>& ord){
    int fc = 0;
    for (int v : ord){
        fc += graph.eliminate_vertex(v);
    }
    return fc;
}

template <typename ScoreFunction> std::vector<int> greedy_ordering(Graph& graph, ScoreFunction score){
    int total_active = graph.active_vertices().size();
    int removed = 0;
    int min_score;
    int min_score_v;
    int v_score;

    std::vector<int> res(total_active);
    while (removed < total_active){
        min_score = INT_MAX;
        min_score_v = INT_MAX;
        for (int v: graph.active_vertices()){
            v_score = score(graph,v);
            if (v_score < min_score) {
                min_score = v_score;
                min_score_v = v;
            }
            else if (v_score == min_score and v < min_score_v) min_score_v = v;
        }
        res[removed] = min_score_v;
        graph.eliminate_vertex(min_score_v);
        removed++;
    }
    return res;
}

//Minimum degree ordering implementation
std::vector<int> minimum_degree_ordering(Graph graph){
    auto score = [](const Graph& g, int v){return g.degree(v);};
    return greedy_ordering(graph,score);
}

std::vector<int> minimum_fillcost_ordering(Graph graph){
    auto score = [](const Graph& g, int v){return g.fill_cost(v);};
    return greedy_ordering(graph,score);
}