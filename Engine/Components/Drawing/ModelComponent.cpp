//
// Created by pedro-souza on 20/04/2026.
//

#include "ModelComponent.h"
#include "../../Actors/Actor.h"
#include "../../Renderer/Texture.h"
#include "../../Renderer/Model.h"
#include "../../Renderer/VertexArray.h"
#include "../../Renderer/Mesh.h"
#include <GL/glew.h>
#include "../../Renderer/Shader.h"
#include "Game.h"

ModelComponent::ModelComponent(Actor* owner)
    : Component(owner)
    , mModel(nullptr)
    , mTextureIndex(0)
    , mIsVisible(true)
    , mRendererIndex(-1)
{
    mOwner->GetGame()->GetRenderer()->AddModelComponent(this);
}

ModelComponent::~ModelComponent() {
    mOwner->GetGame()->GetRenderer()->RemoveModelComponent(mRendererIndex);
}

void ModelComponent::Draw(Shader *shader, const RendererMode mode) {
    if (mModel && mIsVisible) {
        shader->SetMatrixUniform("modelTransform", mOwner->GetWorldTransform());

        if (const Texture *texture = mModel->GetTexture(mTextureIndex)) {
            texture->SetActive();
        }

        const VertexArray *vertexArray = mModel->GetMesh()->GetVertexArray();
        vertexArray->SetActive();

        if (mode == RendererMode::TRIANGLES) {
            glDrawElements(GL_TRIANGLES, vertexArray->GetNumIndices(), GL_UNSIGNED_INT, nullptr);
        }else {
            glDrawElements(GL_LINES, vertexArray->GetNumIndices(), GL_UNSIGNED_INT, nullptr);
        }
    }
}
