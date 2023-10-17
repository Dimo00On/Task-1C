#include "Graph.h"

Graph::Graph(std::vector<std::pair<int, int>>& edges) {
    for (auto new_edge : edges) {
        add(new_edge.first, new_edge.second);
        add(new_edge.second, new_edge.first);
    }
}

std::unordered_set<int>& Graph::neighbours(int vertex) {
    return edges_[vertex];
}

std::unordered_map<int, std::unordered_set<int>>& Graph::edges() {
    return edges_;
}

std::vector<int> Graph::get_vertices_vector() {
    std::vector<int> all_vertices;
    for (auto const& [key, value] : edges_) {
        all_vertices.emplace_back(key);
    }
    return all_vertices;
}

size_t Graph::size() const{
    return graph_size_;
}

void Graph::add(int first, int second) {
    if (edges_.find(first) == edges_.end()) {
        edges_[first] = {second};
        ++graph_size_;
    } else {
        edges_[first].insert(second);
    }
}