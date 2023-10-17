#include "Graph.h"

class SolutionFinder {
    Graph graph_;
    std::vector<int> all_vertices_;
    std::unordered_set<int> current_answer_;
  public:
    SolutionFinder(Graph graph);

    static Graph read_input(std::istream& in);

    std::unordered_set<int> find_exact_solution_small_graph();
    std::unordered_set<int> find_solution_big_graph();
    bool check_answer();
    void print_answer(std::ostream& out);
    std::unordered_set<int> get_solution();

private:
    void try_samples(size_t step, bool& result);
};

