#pragma once

#include <vector>
#include <string>
#include "PriorityMatrix.hpp"

namespace ahp {

    class AHPSolver {
    public:
        AHPSolver(std::vector<std::string> candidates, std::vector<PriorityMatrix> criteria_matrices);
    private:
        size_t candidates_count;
        size_t criteria_count;
        std::vector<std::string> candidates;
        std::vector<PriorityMatrix> criteria_matrices;
    };

}

