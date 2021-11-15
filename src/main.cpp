#include <iostream>

#include "AHP/JsonParser.hpp"
#include "AHP/AHPSolver.hpp"

int main(int, char**) {

    ahp::JsonContainer container("../res/scratch2.json");

    ahp::AHPSolver solver(container);

    ahp::ranking candidates_ranking = solver.getRanking();

    for (int i = 0; i < candidates_ranking.candidates.size(); ++i) {
        std::cout << candidates_ranking.candidates[i] << ": " << candidates_ranking.priorities[i] << std::endl;
    }

}
