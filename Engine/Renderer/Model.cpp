//
// Created by pedro-souza on 20/04/2026.
//

#include "Model.h"
#include <SDL_log.h>
#include "Renderer.h"
#include "../Utils/JsonUtil.h"

Model::Model() :mMesh(nullptr) {}

bool Model::LoadFromJson(const std::string &fileName, Renderer* renderer) {
    nlohmann::json modelJson;

    if (const std::vector<std::string> requiredFields = {"name", "objectFile", "textureFiles"}; !
        JsonUtil::LoadAndValidate(fileName, requiredFields, modelJson)) {
        return false;
    }

    nlohmann::json texturesJson = modelJson["textureFiles"];
    if (!texturesJson.is_array() || !texturesJson.size()) {
        SDL_Log(("Empty textures list"));
        return false;
    }

    for (auto &textureJson: texturesJson) {
        auto textureName = textureJson.get<std::string>();
        Texture *texture = renderer->GetTexture(textureName);
        if (!texture) {
            SDL_Log("Invalid texture name: %s", textureName.c_str());
            return false;
        }
        mTextures.emplace_back(texture);
    }

    const nlohmann::json meshJson = modelJson["objectFile"];
    const auto meshName = meshJson.get<std::string>();

    mMesh = renderer->GetMesh(meshName);
    if (!mMesh) {
        SDL_Log(("Failed to load mesh: %s", meshName.c_str()));
        return false;
    }

    return true;
}

Texture* Model::GetTexture(const size_t textureIndex) const {
    if (textureIndex < mTextures.size()){
        return mTextures[textureIndex];
    }
    return nullptr;
}
