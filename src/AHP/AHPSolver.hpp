#pragma once

#include <vector>
#include <string>
#include "PriorityMatrix.hpp"
#include "JsonParser.hpp"

namespace ahp {

    struct ranking{
        std::vector<std::string> candidates;
        std::vector<double> priorities;
    };

    class AHPSolver {
    public:
        explicit AHPSolver(JsonContainer container);
        ranking getRanking();
    private:


        JsonContainer container;
    };

}

