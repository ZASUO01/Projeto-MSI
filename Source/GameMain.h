//
// Created by pedro-souza on 27/04/2026.
//
#pragma once
#include "Engine/Core/Game.h"

class GameMain :public Game {
public:
    explicit GameMain(const GameConstants& constants);

protected:
    bool InitGameMain() override;
};