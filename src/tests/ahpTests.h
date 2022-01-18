#ifndef DECISION_MAKING_AHP_AHPTESTS_H
#define DECISION_MAKING_AHP_AHPTESTS_H

#include "../AHP/AHPSolver.hpp"
#include "../AHP/JsonContainer.hpp"

class ahpTests {
private:
    static void ahpSolverTest();
public:
    static void test();
    static bool compareDouble(double a, double b);


};


#endif //DECISION_MAKING_AHP_AHPTESTS_H
