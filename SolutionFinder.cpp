#include "SolutionFinder.h"
#include <iostream>
#include <algorithm>
#include <utility>

SolutionFinder::SolutionFinder(Graph graph) :
    graph_(std::move(graph)), all_vertices_(graph_.get_vertices_vector()) {}


Graph SolutionFinder::read_input(std::istream& in) {
    int vertex_amount;
    in >> vertex_amount;
    int first, second;
    std::vector<std::pair<int, int>> edges;
    for (int i = 0; i < vertex_amount; ++i) {
        in >> first >> second;
        edges.emplace_back(first, second);
    }
    return Graph(edges);
}

void SolutionFinder::print_answer(std::ostream& out) {
    out << current_answer_.size() << std::endl;
    for (auto vertex : current_answer_) {
        out << vertex << " ";
    }
    out << std::endl;
}

std::unordered_set<int> SolutionFinder::get_solution() {
    return current_answer_;
}

std::unordered_set<int> SolutionFinder::find_exact_solution_small_graph() {
    bool result = false;
    try_samples( 0, result);
    return current_answer_;
}

std::unordered_set<int> SolutionFinder::find_solution_big_graph() {
    return {};
}

void SolutionFinder::try_samples(size_t step, bool& result) {
    if (step == all_vertices_.size()) {
        result = check_answer();
        return;
    }
    try_samples(step + 1, result);
    if (result) {
        return;
    }
    auto pos = current_answer_.insert(all_vertices_[step]).first;
    try_samples(step + 1, result);
    if (result) {
        return;
    }
    current_answer_.erase(pos);
}

bool SolutionFinder::check_answer() {
    std::unordered_map<int, size_t> goodness;
    for (auto const& [key, value] : graph_.edges()) {
        goodness[key] = 2 * current_answer_.count(key);
        size_t infected_around = 0;
        for (auto neighbour : graph_.neighbours(key)) {
            infected_around += current_answer_.count(neighbour);
        }
        goodness[key] += infected_around;
    }
    return std::all_of(goodness.begin(), goodness.end(),
                       [](std::pair<const int, size_t> val) { return val.second > 1; });
}