//
// Created by pedro-souza on 19/04/2026.
//
#include "Game.h"
#include "Utils/Random.h"
#include "Renderer/Renderer.h"
#include "Actors/Actor.h"
#include <SDL_image.h>
#include <algorithm>
#include <utility>

Game::Game(GameConstants gameConstants)
:mWindow(nullptr)
,mRenderer(nullptr)
,mTicksCount(0)
,mIsRunning(true)
,mIsDebugging(false)
,mUpdatingActors(false)
,mGameConstants(std::move(gameConstants))
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
        if (const int sleepTime = 1000 / mGameConstants.FPS - (SDL_GetTicks() - mTicksCount); sleepTime > 0){
            SDL_Delay(sleepTime);
        }
    }
}

void Game::Shutdown(){
    // Remove actors
    while (!mActors.empty()) {
        delete mActors.back();
    }

    mRenderer->Shutdown();
    delete mRenderer;
    mRenderer = nullptr;

    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}

void Game::UpdateActors(const float deltaTime){
    mUpdatingActors = true;
    for (const auto actor : mActors){
        actor->Update(deltaTime);
    }
    mUpdatingActors = false;

    if (!mPendingActors.empty()) {
        mActors.insert(mActors.end(), mPendingActors.begin(), mPendingActors.end());
        mPendingActors.clear();
    }

    const auto it = std::ranges::remove_if(mActors, [](const Actor* actor) {
        if (actor->GetState() == ActorState::Destroy) {
            delete actor;
            return true;
        }
        return false;
    }).begin();

    mActors.erase(it, mActors.end());
}

void Game::AddActor(Actor* actor){
    if (mUpdatingActors){
        mPendingActors.emplace_back(actor);
    }
    else{
        actor->mGameIndex = static_cast<int>(mActors.size());
        mActors.emplace_back(actor);
    }
}

void Game::RemoveActor(Actor* actor){
    if (actor->mGameIndex < 0 || actor->mGameIndex >= mActors.size()) {
        // if not in mActor, maybe is in mPendingActors
        // use erase patern as we expect just few members in mPendingActors
        std::erase(mPendingActors, actor);
        return;
    }

    const int indexToRemove = actor->mGameIndex;
    Actor* lastActor = mActors.back();

    mActors[indexToRemove] = lastActor;
    lastActor->mGameIndex = indexToRemove;

    mActors.pop_back();

    actor->mGameIndex = -1;
}

void Game::ProcessInput(){
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

void Game::UpdateGame(const float deltaTime){
    // Update all actors and pending actors
    UpdateActors(deltaTime);
}

void Game::GenerateOutput() const {
    Renderer::Clear();

    mRenderer->Draw();

    mRenderer->Present();
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
        static_cast<int>(mGameConstants.WINDOW_WIDTH),
        static_cast<int>(mGameConstants.WINDOW_HEIGHT),
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
