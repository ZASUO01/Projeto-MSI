//
// Created by pedro-souza on 16/04/2026.
//
#pragma once

class VertexArray{
public:
    VertexArray(const float* vertices, unsigned int numVertices, const unsigned int* indices,
                unsigned int numIndices);
    ~VertexArray();

    void SetActive() const;
    unsigned int GetNumIndices() const { return mNumIndices; }
    unsigned int GetNumVertices() const { return mNumVertices; }

private:
    unsigned int mNumVertices;
    unsigned int mNumIndices;
    unsigned int mVertexBuffer;
    unsigned int mIndexBuffer;
    unsigned int mVertexArray;
};