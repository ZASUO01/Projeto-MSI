//
// Created by pedro-souza on 29/04/2026.
//
#pragma once
#include <string>
#include <vector>
#include "Math.h"

namespace  ObjectHelper {
    struct ObjectBounds {
        Vector3 minPoint;
        Vector3 maxPoint;
        float radius;
    };

    bool LoadFromFile(const std::string &fileName, std::vector<float> &outVertices, std::vector<unsigned int> &outIndices, ObjectBounds &outBounds);
};