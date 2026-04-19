//
// Created by pedro-souza on 19/04/2026.
//
#pragma once
#include "../Engine/Game.h"

class GameMain : public Game {
public:
    explicit GameMain(const GameConstants &gameConstants);

protected:
    bool InitGameMain() override;
};
