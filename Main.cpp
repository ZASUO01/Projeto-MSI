//
// Created by pedro-souza on 19/04/2026.
//

#include "Source/GameMain.h"

int main() {
    const GameConstants constants = {
        1024,
        768,
        60,
        "Arcana Digitalis"
    };

    GameMain game(constants);
    if (game.Initialize()) {
        game.RunLoop();
    }
    game.Shutdown();

    return 0;
}
