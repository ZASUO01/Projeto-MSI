//
// Created by pedro-souza on 28/04/2026.
//
#include "VertexArray.h"
#include <GL/glew.h>

/**
 * @brief Vertex array constructor initializes the vertices and indices data into GPU.
 * @param vertices All vertices with all coordinates.
 * @param numVertices Total number of vertices.
 * @param indices All indices of the vertices describing faces.
 * @param numIndices Total number of indices.
 * @param stride It describes how many values a vertex has.
 * @param layout Descriptive list of vertex attributes.
 */
VertexArray::VertexArray(const float *vertices, const unsigned int numVertices, const unsigned int *indices,
                         const unsigned int numIndices, const unsigned int stride,
                         std::vector<VertexAttribute> &layout)
: mNumVertices(numVertices)
, mNumIndices(numIndices)
, mStride(stride)
, mVertexBuffer(0)
, mIndexBuffer(0)
, mVertexArray(0)
{
    // Create vertex array
    glGenVertexArrays(1, &mVertexArray);
    glBindVertexArray(mVertexArray);

    // Create vertex buffer
    glGenBuffers(1, &mVertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, numVertices * stride, vertices, GL_STATIC_DRAW);

    // Create index buffer
    glGenBuffers(1, &mIndexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(GLuint), indices, GL_STATIC_DRAW);

    for (const auto&[index, size, type, normalized, offset] : layout){
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(
            index,
            size,
            type,
            normalized ? GL_TRUE : GL_FALSE,
            stride,
            reinterpret_cast<void*>(offset)
        );
    }
}

/**
 * @brief Destructor delete the vertices and metadata from the GPU.
 */
VertexArray::~VertexArray() {
    glDeleteBuffers(1, &mVertexBuffer);
    glDeleteBuffers(1, &mIndexBuffer);
    glDeleteVertexArrays(1, &mVertexArray);
}

/**
 * @brief Set this vertex array active in the GPU.
 */
void VertexArray::SetActive() const {
    glBindVertexArray(mVertexArray);
}