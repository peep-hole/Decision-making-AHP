#include "JsonContainer.hpp"

using json = nlohmann::json;

namespace ahp {

    JsonContainer::JsonContainer(const std::string &filename) {
        std::ifstream reader(filename);
        json j;
        reader >> j;
        reader.close();
        int criteria_count = 0;
        for(; j["criteria"][criteria_count] != nullptr; ++criteria_count);

        criteria = std::vector<std::string>(criteria_count);

        for(int i = 0; i < criteria_count; ++i) {
            criteria[i] = j["criteria"][i];
        }

        criteria_comparison = std::vector<std::vector<double>>(criteria_count, std::vector<double>(criteria_count));

        for (int i = 0; i < criteria_count; ++i) {
            for (int k = 0; k < criteria_count; ++k) {
                criteria_comparison[i][k] = j["criteria_comparison"][i][k];
            }
        }

        int candidates_count = 0;
        for(; j["candidates"][candidates_count] != nullptr; ++candidates_count);

        candidates = std::vector<std::string>(candidates_count);
        for (int i = 0; i < candidates_count; ++i) {
            candidates[i] = j["candidates"][i];
        }

        people_comparison = std::vector<std::vector<std::vector<double>>>(criteria_count,
                                                                       std::vector<std::vector<double>>(candidates_count,
                                                                       std::vector<double>(candidates_count)));

        for (int c = 0; c < criteria_count; ++c) {
            for (int i = 0; i < candidates_count; ++i) {
                for (int k = 0; k < candidates_count; ++k) {
                    people_comparison[c][i][k] = j["people_comparison"][c][i][k];
                }
            }
        }


    }
}