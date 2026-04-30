//
// Created by pedro-souza on 29/04/2026.
//

#include "Mesh.h"
#include <SDL_log.h>
#include <vector>
#include "VertexArray.h"
#include "Utils/ObjectHelper.h"
#include <GL/glew.h>

/**
 * @brief Mesh constructor initializes members with default values.
 */
Mesh::Mesh()
:mVertexArray(nullptr)
,mRadius(0) {}

/**
 * @brief Tries to load the mesh vertices and metadata from object file.
 * @param fileName Object file containing the mesh data.
 * @return True if it loads successfully and false otherwise.
 */
bool Mesh::Load(const std::string &fileName) {
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    ObjectHelper::ObjectBounds bounds;

    if (!ObjectHelper::LoadFromFile(fileName, vertices, indices, bounds)) {
        SDL_Log("[Mesh] Failed to load mesh from file %s", fileName.c_str());
        return false;
    }

    mRadius = bounds.radius;

    mBounds[0] = bounds.minPoint;
    mBounds[1] = Vector3(bounds.maxPoint.x, bounds.minPoint.y, bounds.minPoint.z);
    mBounds[2] = Vector3(bounds.minPoint.x, bounds.maxPoint.y, bounds.minPoint.z);
    mBounds[3] = Vector3(bounds.minPoint.x, bounds.minPoint.y, bounds.maxPoint.z);
    mBounds[4] = Vector3(bounds.minPoint.x, bounds.maxPoint.y, bounds.maxPoint.z);
    mBounds[5] = Vector3(bounds.maxPoint.x, bounds.minPoint.y, bounds.maxPoint.z);
    mBounds[6] = Vector3(bounds.maxPoint.x, bounds.maxPoint.y, bounds.minPoint.z);
    mBounds[7] = bounds.maxPoint;

    constexpr unsigned int stride = 8 * sizeof(float); // 8 x 4 bytes;

    std::vector<VertexAttribute> layout;
    layout.emplace_back(0, 3, GL_FLOAT, false, 0);
    layout.emplace_back(1, 3, GL_FLOAT, false, 3 * sizeof(float));
    layout.emplace_back(2, 2, GL_FLOAT, false, 6 * sizeof(float));

    mVertexArray = new VertexArray(vertices.data(), vertices.size() / 8, indices.data(), indices.size(), stride, layout);
    return true;
}

/**
 * @brief Destructor cleans the memory used by the vertex array
 */
void Mesh::Unload() {
    delete mVertexArray;
    mVertexArray = nullptr;
}

