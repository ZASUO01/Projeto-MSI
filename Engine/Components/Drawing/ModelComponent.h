//
// Created by pedro-souza on 20/04/2026.
//
#pragma once

#include "../Component.h"
#include <cstddef>
#include "../../Renderer/Renderer.h"

class ModelComponent : public Component{
public:
    explicit ModelComponent(Actor* owner);
    ~ModelComponent() override;

    // Draw this mesh component
    virtual void Draw(Shader* shader,  RendererMode mode);

    // Set/get the visibility of the mesh
    void SetVisible(const bool visible) { mIsVisible = visible; }
    bool IsVisible() const { return mIsVisible; }

    // Set the mesh/texture index used by mesh component
    virtual void SetModel(Model* model) { mModel = model; }
    void SetTextureIndex(const size_t index) { mTextureIndex = index; }

    void SetRendererIndex(const size_t index) { mRendererIndex = index; }
    size_t GetRendererIndex() const { return mRendererIndex; }

protected:
    Model* mModel;
    size_t mTextureIndex;
    bool mIsVisible;

private:
    // index in the renderer list
    int mRendererIndex;
};
