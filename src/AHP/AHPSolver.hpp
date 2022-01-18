#pragma once

#include <vector>
#include <string>
#include "PriorityMatrix.hpp"
#include "JsonContainer.hpp"

namespace ahp {

    struct ranking{
        bool indicesAvailable;
        std::vector<std::string> candidates;
        std::vector<double> priorities;
        std::vector<std::string> matrixNames;
        std::vector<double> saatyIndices;
        std::vector<double> CRs;

    };

    class AHPSolver {
    public:
        explicit AHPSolver(JsonContainer container);
        ranking getRanking(bool isEVM);

        static void printIndices(ranking candidates_ranking);

        static ranking getRankingFromManyExperts(const std::vector<ranking>& rankings);

    private:

        JsonContainer container;
    };

}

