//
// Created by pedro-souza on 29/04/2026.
//

#include "ObjectHelper.h"

#define TINYOBJ_NO_EXTERN_VAR
#define TINYOBJLOADER_IMPLEMENTATION
#include "tinyobjloader/tiny_obj_loader.h"
#include <filesystem>
#include <SDL2/SDL.h>

/**
 * @brief It tries to load mesh data form an object file.
 * @param fileName The object file containing the mesh vertices and indices.
 * @param outVertices The output vertices vector.
 * @param outIndices  The output indices vector.
 * @param outBounds Bounds data of the box containing the mesh.
 * @return True if it loads successfully and false otherwise.
 */
bool ObjectHelper::LoadFromFile(const std::string &fileName, std::vector<float> &outVertices, std::vector<unsigned int> &outIndices, ObjectBounds &outBounds) {
    if (!std::filesystem::exists(fileName)) {
        SDL_Log("[Object Helper] File does not exist: %s", fileName.c_str());
        return false;
    }

    tinyobj::ObjReaderConfig readerConfig;
    readerConfig.triangulate = true;

    tinyobj::ObjReader reader;

    if (!reader.ParseFromFile(fileName, readerConfig)) {
        if (!reader.Error().empty()) {
            SDL_Log("Failed to parse OBJ file: %s", reader.Error().c_str());
        }
        return false;
    }

    const auto& attrib = reader.GetAttrib();
    const auto& shapes = reader.GetShapes();

    size_t totalIndices = 0;
    for (const auto& shape : shapes) {
        totalIndices += shape.mesh.indices.size();
    }

    outVertices.clear();
    outIndices.clear();

    outVertices.reserve(totalIndices * 8);
    outIndices.reserve(totalIndices);

    float radius = 0.0f;
    Vector3 minPoint(Math::Infinity);
    Vector3 maxPoint(Math::NegInfinity);
    Vector3 pos(0.0f);

    for (const auto& shape : shapes) {
        for (const auto&[vertexIndex, normalIndex, textureCoordIndex] : shape.mesh.indices) {
            pos.x = attrib.vertices[3 * vertexIndex + 0];
            pos.y = attrib.vertices[3 * vertexIndex + 1];
            pos.z = attrib.vertices[3 * vertexIndex + 2];

            outVertices.push_back(pos.x);
            outVertices.push_back(pos.y);
            outVertices.push_back(pos.z);

            minPoint.x = Math::Min(minPoint.x, pos.x);
            minPoint.y = Math::Min(minPoint.y, pos.y);
            minPoint.z = Math::Min(minPoint.z, pos.z);
            maxPoint.x = Math::Max(maxPoint.x, pos.x);
            maxPoint.y = Math::Max(maxPoint.y, pos.y);
            maxPoint.z = Math::Max(maxPoint.z, pos.z);

            radius = Math::Max(radius, pos.LengthSq());

            if (normalIndex >= 0) {
                outVertices.push_back(attrib.normals[3 * normalIndex + 0]);
                outVertices.push_back(attrib.normals[3 * normalIndex + 1]);
                outVertices.push_back(attrib.normals[3 * normalIndex + 2]);
            } else {
                outVertices.insert(outVertices.end(), {0.0f, 0.0f, 0.0f});
            }

            if (textureCoordIndex >= 0) {
                outVertices.push_back(attrib.texcoords[2 * textureCoordIndex + 0]);
                outVertices.push_back(1.0f - attrib.texcoords[2 * textureCoordIndex + 1]);
            } else {
                outVertices.insert(outVertices.end(), {0.0f, 0.0f});
            }

            outIndices.push_back(static_cast<unsigned int>(outIndices.size()));
        }
    }

    outBounds.radius = Math::Sqrt(radius);
    outBounds.minPoint = minPoint;
    outBounds.maxPoint = maxPoint;

    return true;
}