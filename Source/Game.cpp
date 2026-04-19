//
// Created by pedro-souza on 15/04/2026.
//
#include "Game.h"
#include "./Utils/Random.h"
#include <SDL_image.h>

Game::Game()
        :mWindow(nullptr)
        ,mTicksCount(0)
        ,mIsRunning(true)
{}

bool Game::Initialize(){
    Random::Init();

    if (SDL_Init(SDL_INIT_VIDEO) != 0){
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }

    // Init SDL Image
    if (constexpr int imgFlags = IMG_INIT_PNG; !(IMG_Init(imgFlags) & imgFlags)){
        SDL_Log("Unable to initialize SDL_image: %s", IMG_GetError());
        return false;
    }


    mWindow = SDL_CreateWindow(
        "Arcana Digitalis",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

    if (!mWindow){
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }

    mRenderer = new Renderer(mWindow, RendererMode::TRIANGLES);
    if (!mRenderer->Initialize(WINDOW_WIDTH, WINDOW_HEIGHT)) {
        SDL_Log("Failed to initialize renderer: %s", SDL_GetError());
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
        if (const int sleepTime = (1000 / FPS) - (SDL_GetTicks() - mTicksCount); sleepTime > 0){
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
    mRenderer->Clear();

    mRenderer->Draw();

    mRenderer->Present();
}

void Game::Shutdown(){
    mRenderer->Shutdown();
    delete mRenderer;
    mRenderer = nullptr;

    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}