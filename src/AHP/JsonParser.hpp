#pragma once
#include <json/json.hpp>
#include <string>
#include <fstream>
#include <iostream>

namespace ahp {

    class JsonContainer {
    private:
        std::vector<std::string> criteria;
        std::vector<std::string> candidates;
        std::vector<std::vector<float>> criteria_comparison;
        std::vector<std::vector<std::vector<float>>> people_comparison;

    public:
        explicit JsonContainer(const std::string& filename);
    };

    void parse_json(const std::string& filename);
    
}