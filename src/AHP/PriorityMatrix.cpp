#include "PriorityMatrix.hpp"

#include <stdexcept>
#include <iostream>

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

    std::vector<double> PriorityMatrix::get_priorities() const {


        std::vector<double> priorities(size, 0.0);

        std::cout << "PRIORITIES: \n";
        std::cout <<"MATRIX: \n" << matrix <<"\n";


        Eigen::EigenSolver<Eigen::MatrixXd> solver(matrix);

        double sum = 0;

        for (long x = 0; x < size; ++x) {
            priorities[x] = std::abs(solver.eigenvectors()(x, 0).real());
        }



        for (long x = 0; x < size; ++x) {
            std::cout << priorities[x] << " | ";
            sum += priorities[x];
        }

        std::cout << "\n_____________________________\n";

        for (long x = 0; x < size; ++x) {
            priorities[x] /= sum;
        }

        return priorities;


    }
}