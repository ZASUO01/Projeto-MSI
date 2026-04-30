//
// Created by pedro-souza on 29/04/2026.
//
#pragma once
#include <string>
#include <array>
#include "../Utils/Math.h"

class Mesh {
public:
    Mesh();
    ~Mesh() = default;

    bool Load(const std::string &fileName);
    void Unload();

    [[nodiscard]] class VertexArray* GetVertexArray() const { return mVertexArray; }
    float GetRadius() const { return mRadius; }
    const std::array<Vector3, 8>& GetBound() const { return mBounds; }

    float GetDepth() const { return Math::Abs(mBounds[7].x - mBounds[0].x); }
    float GetWidth() const { return Math::Abs(mBounds[7].y - mBounds[0].y); }
    float GetHeight() const { return Math::Abs(mBounds[7].z - mBounds[0].z); }
private:
    VertexArray* mVertexArray;
    std::array<Vector3, 8> mBounds;
    float mRadius;
};

