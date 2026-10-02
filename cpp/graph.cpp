#include "graph.hpp"
#include <vector>
#include <unordered_set>
#include <iterator>
#include <utility>
#include <stdexcept>
#include <cstddef>

Graph :: Graph(std::vector<std::unordered_set<int>> adj) : adjacency(std::move(adj)), active(){
    this -> validate(); 
    for (int i = 0; i < adjacency.size(); i++){
        active.insert(i);
    }    
}

void Graph :: check_vertex(int v) const {
    if (v < 0 or v >= adjacency.size()) {
        throw std :: out_of_range("Invalid vertex ID");
    }
}

void Graph :: add_edge(int u, int v){
    if (u == v){
        throw std::invalid_argument("Added a self-loop");
    }
    this -> check_vertex(v);
    this -> check_vertex(u);
    if (!active.contains(u) or !active.contains(v)){
        throw std::invalid_argument("Tried to add an edge containing an eliminated vertex");
    }
    this -> adjacency[u].insert(v);
    this -> adjacency[v].insert(u);
}

int Graph :: eliminate_vertex(int v){
    this -> check_vertex(v);
    if (!active.contains(v)){
        throw std::invalid_argument("Tried to eliminate an already eliminated vertex");
    }
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
    this -> active.erase(v);
    this -> adjacency[v].clear();
    return fc;
}

int Graph :: degree(int v) const {
    this -> check_vertex(v);
    return this -> adjacency[v].size();
}

bool Graph :: is_active(int v) const {
    this -> check_vertex(v);
    return active.contains(v);
}

int Graph :: vertex_count() const {
    return this -> adjacency.size();
}

void Graph :: validate() const {
    std::size_t u_ctr = 0, v_ctr = 0;
    for (int u = 0; u < adjacency.size(); u++){
        const auto& nei_set = adjacency[u];
        for (int v : nei_set){
            // check if any vertex IDs are negative or oversized
            if (v < 0 or v >= adjacency.size()) {
                throw std::invalid_argument("Invalid vertex ID");
            }
            // check self loops
            if (u == v) {
                throw std::invalid_argument("Self loop");
            }
            // check symmetry
            else if (u < v){
                if (!adjacency[v].contains(u)){
                    throw std::invalid_argument("Not symmetric");
                }
                u_ctr++;
            }
            else {
                v_ctr++;
            }

        }
    }
    if (u_ctr != v_ctr) {
        throw std::invalid_argument("Not symmetric");
    }
    /*u_ctr, v_ctr is a clever way to check symmetry without 
    having to do two hash lookups. 
    Idea is to look at all arrows from smaller to larger vertices.
    Check if the reverse edge exists. 
    If this is true, then the number of arrows from smaller to larger vertices
    is leq number of arrows from larger to smaller.
    Keep a counter of total arrows from smaller to larger and larger to smaller
    If equal, then done. 
*/
}

int Graph :: fill_cost(int v) const {
    auto& nei_set = adjacency[v];
    int fc = 0;
    for (auto it = nei_set.begin(); it != nei_set.end(); ++it){
        for (auto it2 = std::next(it); it2 != nei_set.end(); ++it2){
            check_vertex(v);
            if (!active.contains(v)) {
                throw std::runtime_error("Checking an eliminated vertex");
            }
            if (!adjacency[*it].contains(*it2)){
                fc++;
            }
        }
    }
    return fc;
}

const std::unordered_set<int>& Graph :: active_vertices() const {
    return active;
}

