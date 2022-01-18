#include <iostream>

#include "AHP/JsonContainer.hpp"
#include "AHP/AHPSolver.hpp"

#include "tests/ahpTests.h"

#define DO_TEST

int main(int, char**) {

#ifdef DO_TEST
    ahpTests::test();
#endif

    ahp::JsonContainer container("../res/company_hiring.json");

    ahp::AHPSolver solver(container);

    ahp::ranking candidates_ranking = solver.getRanking(false);

    for (int i = 0; i < candidates_ranking.candidates.size(); ++i) {
        std::cout << candidates_ranking.candidates[i] << ": " << candidates_ranking.priorities[i] << std::endl;
    }

    ahp::AHPSolver::printIndices(candidates_ranking);



}
