//
// Created by pedro-souza on 27/04/2026.
//
#pragma once
#include <SDL2/SDL.h>

/**
 * @brief A struct containing constants to start the game with initial values.
 */
struct GameConstants {
    float WINDOW_WIDTH;
    float WINDOW_HEIGHT;
    int FPS;
    const char *WINDOW_TITLE;
};

class Game {
public:
    explicit Game(const GameConstants &constants);
    virtual ~Game() = default;

    // Main functions
    bool Initialize();

    void RunLoop();
    void Shutdown();
    void Quit() { mIsRunning = false; }

protected:
    virtual bool InitGameMain() = 0;

private:
    static bool InitSDLSubsystems();
    bool InitGameBase();

    void ProcessInput();
    void UpdateGame(float deltaTime);
    void GenerateOutput() const;

    // Rendering members
    SDL_Window *mWindow;
    class Renderer* mRenderer;

    // Assets management
    class AssetManager* mAssetManager;

    // Track elapsed time since game start
    Uint32 mTicksCount;

    // Game control variables
    bool mIsRunning;
    GameConstants mGameConstants;
};
