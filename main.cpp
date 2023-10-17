#include "SolutionFinder.h"
#include <iostream>


int main() {
    auto solution_finder = SolutionFinder(SolutionFinder::read_input(std::cin));
    solution_finder.find_exact_solution_small_graph();
    solution_finder.print_answer(std::cout);
    return 0;
}
