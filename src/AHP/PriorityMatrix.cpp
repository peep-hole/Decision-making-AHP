#include "PriorityMatrix.hpp"

#include <stdexcept>
#include <cmath>

namespace ahp {
    PriorityMatrix::PriorityMatrix(size_t size) :
    size(size),
    matrix(size, size) //init 2d array with 1 in each element
    {

        for (long x=0; x < size; ++x) {
            for (long  y=0; y < size; ++y) {
                matrix(x, y) = 1;
            }
        }

    }

    void PriorityMatrix::set_relation(long a, long b, double value) {
        if(value == 0.0)
            throw std::invalid_argument("Relation cannot be equal zero!");
        matrix(a, b) = value;
        matrix(b, a) = 1.0/value;
    }

    std::vector<double> PriorityMatrix::get_priorities_EVM() const {

        std::vector<double> priorities(size, 0.0);

        Eigen::EigenSolver<Eigen::MatrixXd> solver(matrix);

        double sum = 0;

        for (long x = 0; x < size; ++x) {
            priorities[x] = std::abs(solver.eigenvectors()(x, 0).real());
        }

        for (long x = 0; x < size; ++x) {
            sum += priorities[x];
        }

        for (long x = 0; x < size; ++x) {
            priorities[x] /= sum;
        }

        return priorities;

    }

    std::vector<double> PriorityMatrix::get_priorities_GMM() const {
        std::vector<double> priorities(size, 1.0);

        double sum = 0;

        for (int y = 0; y < size; ++y) {
            for (int x = 0; x < size; ++x) {
                priorities[y] *= matrix(y, x);
            }
            priorities[y] = std::pow(priorities[y], 1.0/(float)size);
            sum += priorities[y];
        }

        for (int x = 0; x < size; ++x) {
            priorities[x] /= sum;
        }

        return priorities;
    }

}