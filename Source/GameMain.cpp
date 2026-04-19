//
// Created by pedro-souza on 19/04/2026.
//
#include "GameMain.h"

#include "Actors/Cube.h"

GameMain::GameMain(const GameConstants &gameConstants) :Game(gameConstants) {}

bool GameMain::InitGameMain() {
    SDL_Log("GAME MAIN INIT");

    auto cube = new Cube(this);
    return true;
}
