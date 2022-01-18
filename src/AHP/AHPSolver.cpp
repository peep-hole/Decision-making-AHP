#include "AHPSolver.hpp"

#include <utility>

namespace ahp {
    AHPSolver::AHPSolver(JsonContainer container) : container(std::move(container)){}

    ranking AHPSolver::getRanking(bool isEVM) {

        ranking result; // ranking for final results
        result.CRs = std::vector<double>();
        result.saatyIndices = std::vector<double>();
        result.matrixNames = std::vector<std::string>();

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

            result.matrixNames.emplace_back("Criteria Comparision");
            result.CRs.push_back(criteria_relations.getCr());
            result.saatyIndices.push_back(criteria_relations.getSaatyIndex());
            result.indicesAvailable = true;

        }
        else {
            criteria_priorities = criteria_relations.get_priorities_GMM();
            result.indicesAvailable = false;

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
                result.matrixNames.emplace_back("Candidates per " + container.criteria[c] + " comparison");
                result.CRs.push_back(candidates_per_criteria_relation[c].getCr());
                result.saatyIndices.push_back(candidates_per_criteria_relation[c].getSaatyIndex());
                result.indicesAvailable = true;

            }
            else {
                candidates_per_criteria_priorities[c] = candidates_per_criteria_relation[c].get_priorities_GMM();
                result.indicesAvailable = false;

            }
        }


        // final ranking

        result.candidates = container.candidates;
        result.priorities = std::vector<double>(candidates_size);



        for (int c = 0; c < candidates_size; ++c) {
            for (int cr = 0; cr < criteria_size; ++cr) {
                result.priorities[c] += candidates_per_criteria_priorities[cr][c] * criteria_priorities[cr];
            }
        }


        return result;
    }

    void AHPSolver::printIndices(ranking candidates_ranking) {
        if (candidates_ranking.indicesAvailable) {
            for (int i = 0; i < candidates_ranking.matrixNames.size(); ++i) {
                std::cout << candidates_ranking.matrixNames[i] << " CR: " << candidates_ranking.CRs[i] << ", Saaty: " <<
                          candidates_ranking.saatyIndices[i] <<"\n";
            }
        }

    }

    ranking AHPSolver::getRankingFromManyExperts(const std::vector<ranking>& rankings) {

        int rankingSize = rankings[0].priorities.size();

        std::vector<double> finalRank(rankingSize, 0);

        for (auto &rank : rankings) {
            for (int i = 0; i < rankingSize; i++) {
                finalRank[i] += rank.priorities[i];
            }
        }

        for (int i = 0; i < rankingSize; i++) {
            finalRank[i] /= (double)finalRank.size();
        }

        ranking newRanking;

        newRanking.priorities = finalRank;
        newRanking.candidates = rankings[0].candidates;
        newRanking.indicesAvailable = false;

        return newRanking;


    }

}
