//
// Created by pedro-souza on 19/04/2026.
//
#pragma once
#include <SDL_stdinc.h>
#include "../Utils/Math.h"

enum class ActorState{
    Active,
    Paused,
    Destroy
};

class Actor{
public:
    explicit Actor(class Game* game);
    virtual ~Actor();

    // Update function called from Game (not overridable)
    void Update(float deltaTime);
    // ProcessInput function called from Game (not overridable)
    void ProcessInput(const Uint8* keyState);

    // Position getter/setter
    Vector3 GetPosition() { return GetWorldTransform().GetTranslation(); }
    void SetPosition(const Vector3& pos) { mPosition = pos; mIsTransformDirty = true; }

    // Scale getter/setter
    const Vector3& GetScale() const { return mScale; }
    void SetScale(const Vector3& scale) { mScale = scale; mIsTransformDirty = true; }

    // Rotation getter/setter
    const Vector3& GetRotation() const { return mRotation; }
    void SetRotation(const Vector3& rotation) { mRotation = rotation; }

    Vector3 GetForward() { return GetWorldTransform().GetXAxis() ;}

    // World transform getter
    const Matrix4& GetWorldTransform();

    // State getter/setter
    ActorState GetState() const { return mState; }
    void SetState(const ActorState state) { mState = state; }

    // Game getter
    Game* GetGame() const { return mGame; }

protected:
    Game* mGame;

    // Any actor-specific update code (overridable)
    virtual void OnUpdate(float deltaTime) {}
    // Any actor-specific update code (overridable)
    virtual void OnProcessInput(const Uint8* keyState) {}

    // Actor's state
    ActorState mState;

    // Transform
    Vector3 mPosition;
    Vector3 mScale;
    Vector3 mRotation;

    Matrix4 mWorldTransform;
    bool mIsTransformDirty;

private:
    // index of this actor in the game actors list. Used to fast removal.
    int mGameIndex;

friend class Game;
};
