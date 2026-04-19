//
// Created by pedro-souza on 19/04/2026.
//
#pragma once
#include "Engine/Actors/Actor.h"

class Cube : public Actor {
public:
    explicit Cube(Game* game);

protected:
    void OnUpdate(float deltaTime) override;
};
