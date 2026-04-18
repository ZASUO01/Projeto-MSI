//
// Created by pedro-souza on 17/04/2026.
//

#include <fstream>
#include "Mesh.h"
#include "VertexArray.h"
#include "../Utils/ObjectLoader.h"


Mesh::Mesh()
: mVertexArray(nullptr)
{}

bool Mesh::Load(const std::string& fileName){
   std::vector<float> vertices;
   std::vector<unsigned int> indices;

    if (!ObjectLoader::Load(fileName, vertices, indices)) {
       return false;
    }

    mVertexArray = new VertexArray(vertices.data(), vertices.size() / 8, indices.data(), indices.size());
    return true;
}

void Mesh::Unload(){
    delete mVertexArray;
    mVertexArray = nullptr;
}