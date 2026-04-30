//
// Created by pedro-souza on 27/04/2026.
//

#include "Game.h"
#include "../Utils/Random.h"
#include "../Renderer/Renderer.h"
#include "AssetManager.h"
#include <SDL_image.h>

/**
 * @brief Game constructor.
 * @param constants Constant values to initialize the game.
 */
Game::Game(const GameConstants& constants)
:mWindow(nullptr)
,mRenderer(nullptr)
,mAssetManager(nullptr)
,mTicksCount(0)
,mIsRunning(true)
,mGameConstants(constants)
{}

/**
 * @brief It initializes all the required systems and members.
 * @return true in case of success and false otherwise.
 */
bool Game::Initialize() {
    if (!InitSDLSubsystems()) {
        return false;
    }

    if (!InitGameBase()) {
        return false;
    }

    if (!InitGameMain()) {
        return false;
    }

    return true;
}

/**
 * @brief Starts running the main game looping.
 */
void Game::RunLoop() {
    while (mIsRunning) {
        // Calculate delta time in seconds
        float deltaTime = static_cast<float>(SDL_GetTicks() - mTicksCount) / 1000.0f;

        if (deltaTime > 0.05f){
            deltaTime = 0.05f;
        }

        mTicksCount = SDL_GetTicks();

        ProcessInput();
        UpdateGame(deltaTime);
        GenerateOutput();

        const int targetMs = 1000 / mGameConstants.FPS;
        const int elapsedMs = static_cast<int>(SDL_GetTicks() - mTicksCount);

        // Sleep to maintain frame rate
        if (const int sleepTime = targetMs - elapsedMs; sleepTime > 0){
            SDL_Delay(static_cast<Uint32>(sleepTime));
        }
    }
}

/**
 * @brief It turns of all the running systems and clears the resources.
 */
void Game::Shutdown()  {
    mRenderer->Shutdown();
    delete mRenderer;
    mRenderer = nullptr;

    mAssetManager->UnloadData();
    delete mAssetManager;
    mAssetManager = nullptr;

    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}

bool Game::InitSDLSubsystems() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Unable to initialize SDL Video: %s", SDL_GetError());
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
        mGameConstants.WINDOW_TITLE,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        static_cast<int>(mGameConstants.WINDOW_WIDTH),
        static_cast<int>(mGameConstants.WINDOW_HEIGHT),
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

    if (!mWindow) {
        SDL_Log("Unable to create SDL window: %s", SDL_GetError());
        return false;
    }

    mRenderer = new Renderer(mWindow);
    if (!mRenderer->Initialize(mGameConstants.WINDOW_WIDTH, mGameConstants.WINDOW_HEIGHT)) {
        mRenderer->Shutdown();
        delete mRenderer;
        return false;
    }

    mAssetManager = new AssetManager();

    return true;
}

void Game::ProcessInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                Quit();
                break;
            default:
                break;
        }
    }
}

void Game::UpdateGame(float deltaTime) {
    // TODO
}

void Game::GenerateOutput() const{
    Renderer::Clear();
    //mRenderer->Draw();

    mRenderer->Present();
}
