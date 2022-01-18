#include "PriorityMatrix.hpp"

#include <stdexcept>
#include <cmath>
#include <iostream>
#include <random>

namespace ahp {
    PriorityMatrix::PriorityMatrix(size_t size) :
    size(size),
    CR(0),
    saatyIndex(0),
    isCalculated(false),
    isEVM(true),
    matrix(size, size) //init 2d array with 1 in each element
    {

        for (long x=0; x < size; ++x) {
            for (long  y=0; y < size; ++y) {
                if(x==y)
                    matrix(x, y) = 1;
                else
                    matrix(x, y) = -1;
            }
        }

    }

    void PriorityMatrix::set_relation(long a, long b, double value) {
        if(value == 0.0)
            throw std::invalid_argument("Relation cannot be equal zero!");
        matrix(a, b) = value;
        matrix(b, a) = 1.0/value;
    }

    Eigen::MatrixXd PriorityMatrix::fix_incompleteness_EVM() const {
        Eigen::MatrixXd new_matrix(size, size);
        for (long  y=0; y < size; ++y) {
            int s = 0;
            for (long x=0; x < size; ++x)
                if(matrix(y, x) == -1)
                    ++s;
            for (long x=0; x < size; ++x) {
                double new_value;
                if(matrix(y, x) == -1 && x != y)
                    new_value = 0.0;
                else if(matrix(y, x) != -1 && x != y)
                    new_value = matrix(y, x);
                else
                    new_value = s+1.0;
                new_matrix(y,x) = new_value;
            }
        }
        return new_matrix;
    }

    Eigen::MatrixXd PriorityMatrix::fix_incompleteness_GMM() const {
        Eigen::MatrixXd new_matrix(size, size);
        for (long x=0; x < size; ++x) {
            for (long  y=0; y < size; ++y) {
                new_matrix(x,y) = matrix(x,y) >= 0 ? matrix(x,y) : 1;
            }
        }
        return new_matrix;
    }

    std::vector<double> PriorityMatrix::get_priorities_EVM(){

        std::vector<double> priorities(size, 0.0);
        
        Eigen::EigenSolver<Eigen::MatrixXd> solver(fix_incompleteness_EVM());

        saatyIndex = std::abs((std::abs(solver.eigenvalues()[0].real()) - (double)size)/((double)size - 1.0));

        Eigen::MatrixXd ri(size, size);

        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> dist6(1,10000);
        for (int y = 0; y < size; ++y) {
            for (int x = 0; x < size; ++x) {
                ri(y, x) = (double)dist6(rng)/10000.0;
            }
        }

        Eigen::EigenSolver<Eigen::MatrixXd> ri_solver(ri);

        double ri_saaty_index = std::abs((std::abs(ri_solver.eigenvalues()[0].real()) - (double)size)/((double)size - 1.0));

        CR = saatyIndex / ri_saaty_index;

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

        isCalculated = true;

        return priorities;

    }

    std::vector<double> PriorityMatrix::get_priorities_GMM() const{
        std::vector<double> priorities(size, 1.0);

        Eigen::MatrixXd new_matrix = fix_incompleteness_GMM();

        double sum = 0;

        for (int y = 0; y < size; ++y) {
            for (int x = 0; x < size; ++x) {
                priorities[y] *= new_matrix(y, x);
            }
            priorities[y] = std::pow(priorities[y], 1.0/(float)size);
            sum += priorities[y];
        }

        for (int x = 0; x < size; ++x) {
            priorities[x] /= sum;
        }

        return priorities;
    }

    void PriorityMatrix::print() {
        for (int y = 0; y < size; ++y) {
            for (int x = 0; x < size; ++x) {
                std::cout << matrix(y,x) << '\t';
            }
            std::cout << '\n';
        }
        isCalculated = true;
        isEVM = false;

    }

    void PriorityMatrix::checkForIndex() const {
        if (!isCalculated) {
            throw std::runtime_error("To get inconsistency ratio or saaty's index, priorities need to be calculated first!\n");
        }

        if(!isEVM) {
            throw std::runtime_error("Inconsistency ratio and saaty's index work with eigenvalue method only!");
        }
    }

    double PriorityMatrix::getCr() const {
        checkForIndex();
        return CR;
    }

    double PriorityMatrix::getSaatyIndex() const {
        checkForIndex();
        return saatyIndex;
    }

}