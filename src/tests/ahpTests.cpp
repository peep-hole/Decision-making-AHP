//
// Created by peephole on 18.01.2022.
//

#include "ahpTests.h"

void ahpTests::ahpSolverTest() {

    {
        // TEST 1 : wikipedia validation , method : EVM  + indices

        ahp::JsonContainer container("../res/wikipedia_validation.json");
        ahp::AHPSolver solver(container);
        ahp::ranking candidates_ranking = solver.getRanking(true);

        assert(ahpTests::compareDouble(candidates_ranking.priorities[0], 0.358137));
        assert(ahpTests::compareDouble(candidates_ranking.priorities[1], 0.492786));
        assert(ahpTests::compareDouble(candidates_ranking.priorities[2], 0.149077));

    }


    {
        // TEST 2 : wikipedia validation , method : GMM

        ahp::JsonContainer container("../res/wikipedia_validation.json");
        ahp::AHPSolver solver(container);
        ahp::ranking candidates_ranking = solver.getRanking(false);

        assert(ahpTests::compareDouble(candidates_ranking.priorities[0], 0.358055));
        assert(ahpTests::compareDouble(candidates_ranking.priorities[1], 0.492185));
        assert(ahpTests::compareDouble(candidates_ranking.priorities[2], 0.149761));
    }

    {
        // TEST 3 : company hiring , method : EVM

        ahp::JsonContainer container("../res/company_hiring.json");
        ahp::AHPSolver solver(container);
        ahp::ranking candidates_ranking = solver.getRanking(true);

        assert(ahpTests::compareDouble(candidates_ranking.priorities[0], 0.459792));
        assert(ahpTests::compareDouble(candidates_ranking.priorities[1], 0.306017));
        assert(ahpTests::compareDouble(candidates_ranking.priorities[2], 0.234191));

    }

    {
        // TEST 4 : company hiring , method : GMM

        ahp::JsonContainer container("../res/company_hiring.json");
        ahp::AHPSolver solver(container);
        ahp::ranking candidates_ranking = solver.getRanking(false);

        assert(ahpTests::compareDouble(candidates_ranking.priorities[0], 0.431487));
        assert(ahpTests::compareDouble(candidates_ranking.priorities[1], 0.324834));
        assert(ahpTests::compareDouble(candidates_ranking.priorities[2], 0.243679));
    }

}

void ahpTests::test() {
    ahpSolverTest();
}

bool ahpTests::compareDouble(double a, double b) {
    double c = a - b;
    if (c < 0) c = -c;
    return c < 0.000001;
}
