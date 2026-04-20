//
// Created by pedro-souza on 19/04/2026.
//
#include "Actor.h"
#include "../Game.h"
#include "../Components/Component.h"
#include <algorithm>

Actor::Actor(Game* game)
        : mGame(game)
        , mState(ActorState::Active)
        , mPosition(Vector3::Zero)
        , mScale(Vector3::One)
        , mRotation(0.0f)
        , mWorldTransform(Matrix4::Identity)
        , mIsTransformDirty(true)
        , mGameIndex(-1)
{
    mGame->AddActor(this);
}

Actor::~Actor(){
    mGame->RemoveActor(this);
}

void Actor::Update(const float deltaTime){
    if (mState == ActorState::Active){
        OnUpdate(deltaTime);
    }
}

void Actor::ProcessInput(const Uint8* keyState){
    if (mState == ActorState::Active){
        OnProcessInput(keyState);
    }
}


const Matrix4& Actor::GetWorldTransform(){
    if (mIsTransformDirty){
        mIsTransformDirty = false;
        mWorldTransform = Matrix4::CreateScale(mScale) *
                          Matrix4::CreateRotationZ(mRotation.z) *
                          Matrix4::CreateRotationX(mRotation.x) *
                          Matrix4::CreateRotationY(mRotation.y) *
                          Matrix4::CreateTranslation(mPosition);
    }

    return mWorldTransform;
}

void Actor::AddComponent(Component* c){
    mComponents.emplace_back(c);
    std::ranges::sort(mComponents, [](const Component* a, const Component* b) {
        return a->GetUpdateOrder() < b->GetUpdateOrder();
    });
}