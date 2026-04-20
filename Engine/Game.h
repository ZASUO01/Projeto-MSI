//
// Created by pedro-souza on 19/04/2026.
//
#pragma once
#include <string>
#include <SDL2/SDL.h>
#include <vector>

struct GameConstants {
    float WINDOW_WIDTH;
    float WINDOW_HEIGHT;
    int FPS;
    std::string WINDOW_TITLE;
};

class Game {
public:
    explicit Game(GameConstants gameConstants);
    virtual ~Game() = default;

    bool Initialize();
    void RunLoop();
    void Shutdown();
    void Quit() { mIsRunning = false; }

    // Actor functions
    void UpdateActors(float deltaTime);
    void AddActor(class Actor* actor);
    void RemoveActor(Actor* actor);

    // Getters
    class Renderer* GetRenderer() const { return mRenderer; }

protected:
    virtual bool InitGameMain() = 0;

    // Rendering stuff
    Renderer *mRenderer;
private:
    static bool InitSDLSystems();
    bool InitGameBase();

    void ProcessInput();
    void UpdateGame(float deltaTime);
    void GenerateOutput() const;

    // Actors
    std::vector<Actor*> mActors;
    std::vector<Actor*> mPendingActors;

    // Rendering stuff
    SDL_Window* mWindow;


    // Track elapsed time since game start
    Uint32 mTicksCount;

    // Game control variables
    bool mIsRunning;
    bool mIsDebugging;
    bool mUpdatingActors;
    GameConstants mGameConstants;
};
