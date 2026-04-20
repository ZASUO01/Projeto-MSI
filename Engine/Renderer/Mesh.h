//
// Created by pedro-souza on 17/04/2026.
//
#pragma once
#include <string>
#include <vector>

class Mesh{
public:
    Mesh();
    ~Mesh() = default;

    // Load/unload model
    bool Load(const std::string& fileName);
    void Unload();

    // Get the vertex array associated with this model
    [[nodiscard]] class VertexArray* GetVertexArray() const { return mVertexArray; }
private:
    // Vertex array associated with this model
    VertexArray* mVertexArray;
};