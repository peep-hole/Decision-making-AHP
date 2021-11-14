#include <iostream>

#include <json/json.hpp>

#include "AHP/PriorityMatrix.hpp"

int main(int, char**) {
    ahp::PriorityMatrix mat(3);
    mat.set_relation(0, 1, 5);
    mat.set_relation(0, 2, 9);
    mat.set_relation(1, 2, 4);

    for(auto& it : mat.get_priorities()) {
        std::cout << it << ' ';
    }

}
