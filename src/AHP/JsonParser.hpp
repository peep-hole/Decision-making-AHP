#pragma once
#include <json/json.hpp>
#include <string>
#include <fstream>
#include <iostream>

namespace ahp {

    class JsonContainer {
    public:
        explicit JsonContainer(const std::string& filename);
        std::vector<std::string> criteria;
        std::vector<std::string> candidates;
        std::vector<std::vector<double>> criteria_comparison;
        std::vector<std::vector<std::vector<double>>> people_comparison;
    };
}