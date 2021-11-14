#include "AHPSolver.hpp"

#include <iostream>
namespace ahp {
    AHPSolver::AHPSolver(std::vector<std::string> candidates, std::vector<PriorityMatrix> criteria_matrices) :
    candidates_count(candidates.size()),
    criterias_count(criteria_matrices.size()),
    candidates(candidates),
    criteria_matrices(criteria_matrices)
    {
        
    }
}
