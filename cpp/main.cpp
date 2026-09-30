#include <iostream>
#include <vector>
#include <unordered_set>
#include <iterator>
#include <cassert>
int eliminated_vertex(std::vector<std::unordered_set<int>>& adj, int v){
    
    auto& nei_set = adj[v]; // pass by reference
    int fill_count = 0;
    for (auto it = nei_set.begin(); it != nei_set.end(); ++it){ 
        //use iterators for less memory, instead of temp vector
        int v1 = *it;
        for (auto it2 = std::next(it); it2 != nei_set.end(); ++it2){
            int v2 = *it2;
            if (!adj[v1].contains(v2)){
                adj[v1].insert(v2);
                adj[v2].insert(v1);
                fill_count++;
            }

        }
        adj[v1].erase(v);
    }
    nei_set.clear();
    return fill_count;

}
int evaluate_ordering(std::vector<std::unordered_set<int>> adj, const std::vector<int>& ord){
    int fc = 0;
    for (int v : ord){
        fc += eliminated_vertex(adj,v);
    }
    return fc;
}
int main(){
    std::vector<std::unordered_set<int>> adjacency(4);
    adjacency[0].insert({1,2,3});
    for (int i = 1; i < 4; i++){
        adjacency[i].insert(0);
    }
    int fc = eliminated_vertex(adjacency, 0);
    std::cout << fc << '\n';
    assert(adjacency[0].empty());
    assert((adjacency[1] == std::unordered_set<int>{2,3}));
    assert((adjacency[2] == std::unordered_set<int>{1,3}));
    assert((adjacency[3] == std::unordered_set<int>{1,2}));
    assert(fc == 3);
    return 0;
}