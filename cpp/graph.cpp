#include "graph.hpp"
#include <vector>
#include <unordered_set>
#include <iterator>
#include <utility>
#include <stdexcept>

Graph :: Graph(std::vector<std::unordered_set<int>> adj) : adjacency(std::move(adj)), active(adjacency.size(),true){
    this -> validate(); 
    // Only need to write validate();, but included this -> for learning

}

void Graph :: add_edge(int u, int v){
    this -> adjacency[u].insert(v);
    this -> adjacency[v].insert(u);
}

int Graph :: eliminate_vertex(int v){
    auto& nei_set = this -> adjacency[v];
    int fc = 0;
    for (auto it = nei_set.begin(); it != nei_set.end(); ++it){
        int v1 = *it;
        for (auto it2 = std::next(it); it2 != nei_set.end(); ++it2){
            int v2 = *it2;
            if (!(this -> adjacency)[v1].contains(v2)){
                this -> adjacency[v1].insert(v2);
                this -> adjacency[v2].insert(v1);
                fc++ ;
            }
        }
        this -> adjacency[v1].erase(v);
    }
    this -> active[v] = false;
    this -> adjacency[v].clear();
    return fc;
}

int Graph :: degree(int v) const {
    return this -> adjacency[v].size();
}

bool Graph :: is_active(int v) const {
    return this -> active[v];
}

int Graph :: vertex_count() const {
    return this -> active.size();
}

void Graph :: validate() const {

}

