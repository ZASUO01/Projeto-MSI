//
// Created by pedro-souza on 19/04/2026.
//
#include "Game.h"
#include "Utils/Random.h"
#include <SDL_image.h>

#include "Renderer/Renderer.h"

Game::Game(const GameConstants &gameConstants)
:mRenderer(nullptr)
,mTicksCount(0)
,mIsRunning(true)
,mGameConstants(gameConstants)
{}

bool Game::Initialize(){
    if (!InitSDLSystems()) {
        return false;
    }

    if (!InitGameBase()) {
        return false;
    }

    if (!InitGameMain()) {
        return false;
    }

    mTicksCount = SDL_GetTicks();

    return true;
}

void Game::RunLoop(){
    while (mIsRunning){
        // Calculate delta time in seconds
        float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;

        if (deltaTime > 0.05f){
            deltaTime = 0.05f;
        }

        mTicksCount = SDL_GetTicks();

        ProcessInput();
        UpdateGame(deltaTime);
        GenerateOutput();

        // Sleep to maintain frame rate
        if (const int sleepTime = (1000 / mGameConstants.FPS) - (SDL_GetTicks() - mTicksCount); sleepTime > 0){
            SDL_Delay(sleepTime);
        }
    }
}

void Game::ProcessInput(){
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                Quit();
                break;
        }
    }
}

void Game::UpdateGame(const float deltaTime){
    // TODO
}

void Game::GenerateOutput() const {
    // TODO
}

void Game::Shutdown(){
    mRenderer->Shutdown();
    delete mRenderer;
    mRenderer = nullptr;

    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}


bool Game::InitSDLSystems() {
    // Init SDL Image
    if (SDL_Init(SDL_INIT_VIDEO) != 0){
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }

    // Init SDL Image
    if (constexpr int imgFlags = IMG_INIT_PNG; !(IMG_Init(imgFlags) & imgFlags)){
        SDL_Log("Unable to initialize SDL_image: %s", IMG_GetError());
        return false;
    }

    return true;
}

bool Game::InitGameBase() {
    Random::Init();

    mWindow = SDL_CreateWindow(
        mGameConstants.WINDOW_TITLE.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        mGameConstants.WINDOW_WIDTH,
        mGameConstants.WINDOW_HEIGHT,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

    if (!mWindow){
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }

    mRenderer = new Renderer(mWindow, RendererMode::TRIANGLES);
    if (!mRenderer->Initialize(mGameConstants.WINDOW_WIDTH, mGameConstants.WINDOW_HEIGHT)) {
        SDL_Log("Failed to initialize renderer: %s", SDL_GetError());
        return false;
    }

    return true;
}
