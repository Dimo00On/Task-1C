#include "SolutionFinder.h"
#include <iostream>


int main() {
    auto graph = SolutionFinder::read_input(std::cin);
    auto solution_finder = SolutionFinder(graph);
    solution_finder.find_solution();
    auto solution = solution_finder.get_solution();
    solution_finder.print_answer(std::cout);
    return 0;
}
