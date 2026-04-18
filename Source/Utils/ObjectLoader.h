//
// Created by pedro-souza on 17/04/2026.
//
#pragma once

#include <string>
#include <vector>

namespace  ObjectLoader {
    bool Load(const std::string &fileName, std::vector<float> &outVertices,
                     std::vector<unsigned int> &outIndices);
};
