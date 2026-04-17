#include "VertexArray.h"
#include <GL/glew.h>

VertexArray::VertexArray(const float* vertices, const unsigned int numVertices, const unsigned int* indices,
                         const unsigned int numIndices)
: mNumVertices(numVertices)
, mNumIndices(numIndices)
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
    glBufferData(GL_ARRAY_BUFFER, numVertices * 8 * sizeof(float), vertices, GL_STATIC_DRAW);

    // Create index buffer
    glGenBuffers(1, &mIndexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(GLuint), indices, GL_STATIC_DRAW);

    // Specify the vertex attributes (For now, assume one vertex format) Position is 3 floats
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), nullptr);
    // Normal is 3 floats
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          reinterpret_cast<void*>(sizeof(float) * 3));
    // Texture coordinates is 2 floats
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          reinterpret_cast<void*>(sizeof(float) * 6));
}

VertexArray::~VertexArray(){
    glDeleteBuffers(1, &mVertexBuffer);
    glDeleteBuffers(1, &mIndexBuffer);
    glDeleteVertexArrays(1, &mVertexArray);
}

void VertexArray::SetActive() const{
    glBindVertexArray(mVertexArray);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
}