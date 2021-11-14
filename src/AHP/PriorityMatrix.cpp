#include "PriorityMatrix.hpp"

#include <stdexcept>

namespace ahp {
    PriorityMatrix::PriorityMatrix(size_t size) :
    size(size),
    matrix(size, std::vector<double>(size, 1.0)) //init 2d array with 1 in each element
    {

    }

    void PriorityMatrix::set_relation(size_t a, size_t b, double value) {
        if(value == 0.0)
            throw std::invalid_argument("Relation cannot be equal zero!");
        matrix[a][b] = value;
        matrix[b][a] = 1.0/value;
    }

    std::vector<double> PriorityMatrix::get_priorities() const {
        std::vector<double> buffer(size, 0.0);
        for(size_t x = 0u; x<size; ++x) {
            for(size_t y = 0u; y<size; ++y)
                buffer[x] += matrix[y][x];
        }

        std::vector<double> priorities(size, 0.0);
        for(size_t y = 0u; y<size; ++y) {
            for(size_t x = 0u; x<size; ++x)
                priorities[y] += matrix[y][x] / buffer[x];
            priorities[y] /= static_cast<double>(size);
        }

        return priorities;
    }
}