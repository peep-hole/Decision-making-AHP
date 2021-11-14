#pragma once

#include <vector>

namespace ahp {
    class PriorityMatrix {
    public:
        explicit PriorityMatrix(size_t size);

        void set_relation(size_t a, size_t b, double value);

        std::vector<double> get_priorities() const;
    private:
        size_t size;
        std::vector<std::vector<double>> matrix;
    };
}