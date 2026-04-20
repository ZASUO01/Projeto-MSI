//
// Created by pedro-souza on 20/04/2026.
//
#pragma once
#include <string>
#include <vector>
#include "nlohmann/json.h"

namespace  JsonUtil {
    using json = nlohmann::json;
    bool LoadAndValidate(const std::string &fileName, const std::vector<std::string>& requiredFields, json& outJson);
};
