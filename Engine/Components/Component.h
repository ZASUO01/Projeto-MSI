//
// Created by pedro-souza on 20/04/2026.
//
#pragma once
#include <SDL_stdinc.h>

class Component{
public:
    // Constructor
    // (the lower the update order, the earlier the component updates)
    explicit Component(class Actor* owner, int updateOrder = 100);
    // Destructor
    virtual ~Component() = default;
    // Update this component by delta time
    virtual void Update(float deltaTime);
    // Process input for this component (if needed)
    virtual void ProcessInput(const Uint8* keyState);
    // Debug draw for this component (if needed)
    virtual void DebugDraw(class Renderer* renderer);

    int GetUpdateOrder() const { return mUpdateOrder; }
    Actor* GetOwner() const { return mOwner; }
    class Game* GetGame() const;

    void SetEnabled(const bool enabled) { mIsEnabled = enabled; };
    bool IsEnabled() const { return mIsEnabled; };

protected:
    // Owning actor
    Actor* mOwner;
    // Update order
    int mUpdateOrder;
    // Is component enabled
    bool mIsEnabled;
};
