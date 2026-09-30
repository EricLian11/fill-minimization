#pragma once
#include <vector>
#include <unordered_set>
class Graph {
private:
    std::vector<std::unordered_set<int>> adjacency;
    std::vector<bool> active;
public:
    
    Graph(std::vector<std::unordered_set<int>> adj);

    //add edge in graph
    void add_edge(int u, int v);

    //eliminate vertex from graph, return fill count
    int eliminate_vertex(int v);

    //Returns degree of vertex 
    int degree(int v) const;

    //Returns true if vertex is active
    bool is_active(int v) const;

    //Returns original number of vertices
    int vertex_count() const;

    //validate adjacency graph, throws exception if not valid
    void validate() const;


};