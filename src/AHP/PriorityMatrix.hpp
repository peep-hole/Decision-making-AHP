#pragma once

#include <vector>
#include <Eigen/Eigenvalues>

namespace ahp {
    class PriorityMatrix {
    public:
        explicit PriorityMatrix(size_t size);

        void set_relation(long a, long b, double value);

        Eigen::MatrixXd fix_incompleteness_EVM() const;
        Eigen::MatrixXd fix_incompleteness_GMM() const;

        std::vector<double> get_priorities_EVM() const;

        std::vector<double> get_priorities_GMM() const;

        void print();
    private:
        size_t size;
        Eigen::MatrixXd matrix;
    };
}