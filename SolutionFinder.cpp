#include "SolutionFinder.h"
#include <algorithm>
#include <iostream>
#include <utility>

SolutionFinder::SolutionFinder(Graph graph) :
    graph_(std::move(graph)), all_vertices_(graph_.get_vertices_vector()) {
    for (auto vertex : all_vertices_) {
        unhandled_.insert(vertex);
    }
}


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
    std::vector<int> answer = {current_answer_.begin(), current_answer_.end()};
    std::sort(answer.begin(), answer.end());
    for (auto vertex : answer) {
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

int SolutionFinder::next_vertex() {
    int next;
    if (!neighbours_near_infected_.empty()) {
        next = *neighbours_near_infected_.begin();
        neighbours_near_infected_.erase(neighbours_near_infected_.begin());
        return next;
    }
    if (!near_infected_.empty()) {
        next = *near_infected_.begin();
        near_infected_.erase(near_infected_.begin());
        return next;
    }
    if (!unhandled_.empty()) {
        next = *unhandled_.begin();
        unhandled_.erase(unhandled_.begin());
        return next;
    }
    throw std::runtime_error("No next vertex");
}

void SolutionFinder::handle_vertex(int next) {
    current_answer_.insert(next);
    handle_epidemic({next});
}

std::unordered_set<int> SolutionFinder::find_solution_big_graph() {
    while (near_infected_.size() + unhandled_.size() + neighbours_near_infected_.size() > 0) {
        int next = next_vertex();
        handle_vertex(next);
    }
    return current_answer_;
}

void SolutionFinder::try_samples(size_t step, bool& result) {
    if (step == all_vertices_.size()) {
        result = check_answer();
        for (auto vertex : all_vertices_) {
            unhandled_.insert(vertex);
        }
        near_infected_.clear();
        neighbours_near_infected_.clear();
        return;
    }
    try_samples(step + 1, result);
    if (result) {
        return;
    }
    auto position = current_answer_.insert(all_vertices_[step]).first;
    try_samples(step + 1, result);
    if (result) {
        return;
    }
    current_answer_.erase(position);
}

bool SolutionFinder::check_answer() {
    handle_epidemic(current_answer_);
    return near_infected_.size() + unhandled_.size() + neighbours_near_infected_.size() == 0;
}

void SolutionFinder::handle_infected(std::unordered_set<int> infected) {
    for (auto vertex : infected) {
        auto position = near_infected_.find(vertex);
        if (position != near_infected_.end()) {
            near_infected_.erase(position);
        }
        position = unhandled_.find(vertex);
        if (position != unhandled_.end()) {
            unhandled_.erase(position);
        }
        position = neighbours_near_infected_.find(vertex);
        if (position != neighbours_near_infected_.end()) {
            neighbours_near_infected_.erase(position);
        }
    }
}

void SolutionFinder::handle_near_infected(std::unordered_set<int>& infected, bool& changed) {
    changed = false;
    std::unordered_set<int> new_infected;
    for (auto vertex: infected) {
        for (auto neighbour: graph_.neighbours(vertex)) {
            auto position = near_infected_.find(neighbour);
            if (position != near_infected_.end()) {
                new_infected.insert(*position);
                near_infected_.erase(position);
                changed = true;
            }
            position = unhandled_.find(neighbour);
            if (position != unhandled_.end()) {
                near_infected_.insert(*position);
                unhandled_.erase(position);
            }
            position = neighbours_near_infected_.find(neighbour);
            if (position != neighbours_near_infected_.end()) {
                near_infected_.insert(*position);
                neighbours_near_infected_.erase(position);
            }
        }
    }
    std::swap(infected, new_infected);
}

void SolutionFinder::handle_neighbours_near_infected() {
    for (auto vertex : near_infected_) {
        for (auto neighbour : graph_.neighbours(vertex)) {
            auto position = unhandled_.find(neighbour);
            if (position != unhandled_.end()) {
                neighbours_near_infected_.insert(*position);
                unhandled_.erase(position);
            }
        }
    }
}

void SolutionFinder::handle_epidemic(std::unordered_set<int> infected) {
    handle_infected(infected);
    bool changed = true;
    while (changed) {
        handle_near_infected(infected, changed);
    }
    handle_neighbours_near_infected();
}

std::unordered_set<int> SolutionFinder::find_solution() {
    if (graph_.size() <= 10) {
        return find_exact_solution_small_graph();
    } else {
        return find_solution_big_graph();
    }
}