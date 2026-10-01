#pragma once
#include <vector>
#include <unordered_set>
class Graph {
private:
    std::vector<std::unordered_set<int>> adjacency;
    std::unordered_set<int> active;
    void check_vertex(int v) const;
public:
    Graph(std::vector<std::unordered_set<int>> adj);

    //add edge in graph
    //Time = O(1)
    void add_edge(int u, int v);

    //eliminate vertex from graph, return fill count
    //Time = O(V^2)
    int eliminate_vertex(int v);

    //Returns degree of vertex 
    //Time = O(1)
    int degree(int v) const;

    //Returns true if vertex is active
    //Time = O(1)
    bool is_active(int v) const;

    //Returns original number of vertices
    //Time = O(1)
    int vertex_count() const;

    //validate adjacency graph, throws exception if not valid
    //Time = O(V+E)
    void validate() const;

    //read-only accessor of active vertices
    const std::unordered_set<int>& active_vertices() const;


};