#include "AHPSolver.hpp"

#include <utility>

namespace ahp {
    AHPSolver::AHPSolver(JsonContainer container) : container(std::move(container)){}

    ranking AHPSolver::getRanking(bool isEVM) {

        // criteria priorities

        size_t criteria_size = container.criteria.size();

        PriorityMatrix criteria_relations(criteria_size);

        for (int i = 0; i < criteria_size; ++i) {
            for (int k = i+1; k < criteria_size; ++k) {
                criteria_relations.set_relation(i, k, container.criteria_comparison[i][k]);
            }
        }
        std::vector<double> criteria_priorities;
        if (isEVM) {
            criteria_priorities = criteria_relations.get_priorities_EVM();
        }
        else {
            criteria_priorities = criteria_relations.get_priorities_GMM();
        }

        // per criteria candidates priorities

        size_t candidates_size = container.candidates.size();

        std::vector<std::vector<double>> candidates_per_criteria_priorities(criteria_size,
                                                                            std::vector<double>(candidates_size));
        std::vector<PriorityMatrix> candidates_per_criteria_relation(criteria_size, PriorityMatrix(candidates_size));

        for (int c = 0; c < criteria_size; ++c) {
            for (int i = 0; i < candidates_size; ++i) {
                for (int k = i + 1; k < candidates_size; ++k) {
                    candidates_per_criteria_relation[c].set_relation(i, k, container.people_comparison[c][i][k]);
                }
            }
            if (isEVM) {
                candidates_per_criteria_priorities[c] = candidates_per_criteria_relation[c].get_priorities_EVM();
            }
            else {
                candidates_per_criteria_priorities[c] = candidates_per_criteria_relation[c].get_priorities_GMM();
            }
        }


        // final ranking


        ranking result;
        result.candidates = container.candidates;
        result.priorities = std::vector<double>(candidates_size);


        for (int c = 0; c < candidates_size; ++c) {
            for (int cr = 0; cr < criteria_size; ++cr) {
                result.priorities[c] += candidates_per_criteria_priorities[cr][c] * criteria_priorities[cr];
            }
        }


        return result;
    }

}
