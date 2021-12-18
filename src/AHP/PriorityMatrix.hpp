#pragma once

#include <vector>
#include <Eigen/Eigenvalues>

namespace ahp {
    class PriorityMatrix {
    public:
        explicit PriorityMatrix(size_t size);

        void set_relation(long a, long b, double value);

        std::vector<double> get_priorities() const;
    private:
        size_t size;
        Eigen::MatrixXd matrix;
    };
}