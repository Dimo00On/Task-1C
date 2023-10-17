#include "Graph.h"

class SolutionFinder {
    Graph graph_;
    std::vector<int> all_vertices_;
    std::unordered_set<int> current_answer_;
    std::unordered_set<int> unhandled_;
    std::unordered_set<int> near_infected_;
    std::unordered_set<int> neighbours_near_infected_;

  public:
    explicit SolutionFinder(Graph graph);

    static Graph read_input(std::istream& in);

    std::unordered_set<int> find_solution();
    std::unordered_set<int> find_exact_solution_small_graph();
    std::unordered_set<int> find_solution_big_graph();
    bool check_answer();
    void print_answer(std::ostream& out);
    std::unordered_set<int> get_solution();

private:
    void try_samples(size_t step, bool& result);
    int next_vertex();
    void handle_vertex(int next);
    void handle_epidemic(std::unordered_set<int> infected);
    void handle_infected(std::unordered_set<int> infected);
    void handle_near_infected(std::unordered_set<int>& infected, bool& changed);
    void handle_neighbours_near_infected();
};

