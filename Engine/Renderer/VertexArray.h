//
// Created by pedro-souza on 28/04/2026.
//
#pragma once
#include <cstddef>
#include <vector>

struct VertexAttribute {
    unsigned int index;
    int size;
    unsigned int type;
    bool normalized;
    size_t offset;
};


class VertexArray{
public:
    VertexArray(const float* vertices, unsigned int numVertices,
                const unsigned int* indices, unsigned int numIndices,
                const unsigned int stride, std::vector<VertexAttribute> &layout);
    ~VertexArray();

    void SetActive() const;
    unsigned int GetNumIndices() const { return mNumIndices; }
    unsigned int GetNumVertices() const { return mNumVertices; }

private:
    unsigned int mNumVertices;
    unsigned int mNumIndices;
    unsigned int mStride;
    unsigned int mVertexBuffer;
    unsigned int mIndexBuffer;
    unsigned int mVertexArray;
};