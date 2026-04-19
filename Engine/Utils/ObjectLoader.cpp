//
// Created by pedro-souza on 17/04/2026.
//
#include "ObjectLoader.h"

#define TINYOBJ_NO_EXTERN_VAR
#define TINYOBJLOADER_IMPLEMENTATION
#include "tinyobjloader/tiny_obj_loader.h"
#include <filesystem>
#include <SDL2/SDL.h>

bool ObjectLoader::Load(const std::string &fileName, std::vector<float> &outVertices, std::vector<unsigned int> &outIndices) {
    if (!std::filesystem::exists(fileName)) {
        SDL_Log("File does not exist: %s", fileName.c_str());
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

    for (const auto& shape : shapes) {
        for (const auto&[vertexIndex, normalIndex, textureCoordIndex] : shape.mesh.indices) {
            outVertices.push_back(attrib.vertices[3 * vertexIndex + 0]);
            outVertices.push_back(attrib.vertices[3 * vertexIndex + 1]);
            outVertices.push_back(attrib.vertices[3 * vertexIndex + 2]);

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

    return true;
}