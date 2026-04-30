//
// Created by pedro-souza on 29/04/2026.
//

#include "AssetManager.h"
#include <ranges>
#include "../Renderer/Mesh.h"
#include "../Renderer/Texture.h"

/**
 * @brief Cleans all the stored resources.
 */
void AssetManager::UnloadData() {
    for (const auto val: mMeshes | std::views::values) {
        val->Unload();
        delete val;
    }
    mTextures.clear();

    for (const auto val: mTextures | std::views::values) {
        val->Unload();
        delete val;
    }
    mTextures.clear();
}

/**
 * @brief Either find or create the target mesh.
 * @param fileName The object file name used as the key to find or create the resource.
 * @return A pointer to the stored mesh.
 */
Mesh* AssetManager::GetMesh(const std::string& fileName) {
    Mesh*& mesh = mMeshes[fileName];
    if (mesh) {
        return mesh;
    }

    mesh = new Mesh();
    if (mesh->Load(fileName)) {
        return mesh;
    }

    delete mesh;
    mMeshes.erase(fileName);
    return nullptr;
}

/**
 * @brief Either find or create the target texture.
 * @param fileName The texture file name used as the key to find or create the resource.
 * @return A pointer to the stored texture.
 */
Texture* AssetManager::GetTexture(const std::string& fileName) {
    Texture*& tex = mTextures[fileName];
    if (tex) {
        return tex;
    }

    tex = new Texture();
    if (tex->Load(fileName)) {
        return tex;
    }

    delete tex;
    mTextures.erase(fileName);
    return nullptr;
}