//
// Created by pedro-souza on 15/04/2026.
//

#pragma once
#include <SDL.h>

class Game {
public:
    Game();

    bool Initialize();
    void RunLoop();
    void Shutdown();
    void Quit() { mIsRunning = false; }

    // Constants
    static constexpr int WINDOW_WIDTH   = 1024;
    static constexpr int WINDOW_HEIGHT  = 768;
    static constexpr int FPS = 60;

private:
    void ProcessInput();
    void UpdateGame(float deltaTime);
    void GenerateOutput();

    // Rendering stuff
    SDL_Window* mWindow;

    // Track elapsed time since game start
    Uint32 mTicksCount;

    // Game control variables
    bool mIsRunning;
};
