//
// Created by pedro-souza on 19/04/2026.
//
#include "GameMain.h"

#include "Actors/Cube.h"
#include "Engine/Components/Drawing/ModelComponent.h"
#include "Engine/Renderer/Model.h"

GameMain::GameMain(const GameConstants &gameConstants) :Game(gameConstants) {}

bool GameMain::InitGameMain() {
    const auto cube = new Cube(this);

    const auto model = new Model();
    model->LoadFromJson("../Assets/Models/Cube.json", mRenderer);
    const auto modelComponent = new ModelComponent(cube);
    modelComponent->SetModel(model);
    modelComponent->SetTextureIndex(1);

    return true;
}
