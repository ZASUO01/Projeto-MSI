//
// Created by pedro-souza on 29/04/2026.
//
#pragma once
#include <string>
#include <unordered_map>

class AssetManager {
public:
    AssetManager() = default;
    ~AssetManager() = default;
    void UnloadData();

    class Mesh* GetMesh(const std::string& fileName);
    class Texture* GetTexture(const std::string &fileName);
private:
    std::unordered_map<std::string, Mesh*> mMeshes;
    std::unordered_map<std::string, Texture*> mTextures;
};