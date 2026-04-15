//
// Created by pedro-souza on 15/04/2026.
//
#include "Game.h"

int main() {
    Game game;
    if (game.Initialize()) {
        game.RunLoop();
    }
    game.Shutdown();

    return 0;
}