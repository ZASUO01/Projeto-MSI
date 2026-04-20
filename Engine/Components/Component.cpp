//
// Created by pedro-souza on 20/04/2026.
//
#include "Component.h"
#include "../Actors/Actor.h"

Component::Component(Actor* owner, const int updateOrder)
          :mOwner(owner)
          ,mUpdateOrder(updateOrder)
          ,mIsEnabled(true)
{
    // Add to actor's vector of components
    mOwner->AddComponent(this);
}


void Component::Update(float deltaTime)
{
}

void Component::ProcessInput(const Uint8* keyState)
{
}

void Component::DebugDraw(class Renderer* renderer)
{
}

class Game* Component::GetGame() const
{
    return mOwner->GetGame();
}


