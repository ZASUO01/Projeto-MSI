//
// Created by pedro-souza on 19/04/2026.
//


#include "Source/GameMain.h"

int main() {
    constexpr GameConstants constants = {
        1024,
        768,
        60,
        "Arcana Digitalis"
    };

    GameMain gameMain(constants);
    if (gameMain.Initialize()) {
        gameMain.RunLoop();
    }
    gameMain.Shutdown();

    return 0;
}
