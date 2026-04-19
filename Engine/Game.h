//
// Created by pedro-souza on 19/04/2026.
//
#pragma once
#include <string>
#include <SDL2/SDL.h>

struct GameConstants {
    int WINDOW_WIDTH;
    int WINDOW_HEIGHT;
    int FPS;
    std::string WINDOW_TITLE;
};

class Game {
public:
    explicit Game(const GameConstants &gameConstants);
    virtual ~Game() = default;

    bool Initialize();
    void RunLoop();
    void Shutdown();
    void Quit() { mIsRunning = false; }

protected:
    virtual bool InitGameMain() = 0;

private:
    static bool InitSDLSystems();
    bool InitGameBase();

    void ProcessInput();
    void UpdateGame(float deltaTime);
    void GenerateOutput() const;

    // Rendering stuff
    SDL_Window* mWindow;

    // Track elapsed time since game start
    Uint32 mTicksCount;

    // Game control variables
    bool mIsRunning;
    GameConstants mGameConstants;
};
