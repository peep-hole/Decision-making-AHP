#ifndef DECISION_MAKING_AHP_AHP_H
#define DECISION_MAKING_AHP_AHP_H

#include <string>

using namespace std;

class AHP_solver {
private:
    int criteriaMatrixSize;
    string* criteria;
    double** criteriaComparisonMatrix;
    int candidatesCount;
    string* candidates;
    double*** candidatesPerCriteriaComparison;

};

#endif //DECISION_MAKING_AHP_AHP_H
