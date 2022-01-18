#pragma once

#include <vector>
#include <Eigen/Eigenvalues>

namespace ahp {
    class PriorityMatrix {

    private:
        size_t size;
        Eigen::MatrixXd matrix;
        double CR;
        double saatyIndex;
        bool isCalculated;
        bool isEVM;
        void checkForIndex() const;
        Eigen::MatrixXd fix_incompleteness_EVM() const;
        Eigen::MatrixXd fix_incompleteness_GMM() const;

    public:
        explicit PriorityMatrix(size_t size);

        void set_relation(long a, long b, double value);

        std::vector<double> get_priorities_EVM();

        std::vector<double> get_priorities_GMM() const;

        double getCr() const;

        double getSaatyIndex() const;

        void print();

    };
}