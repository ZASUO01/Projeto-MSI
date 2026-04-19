//
// Created by pedro-souza on 18/04/2026.
//
#pragma once
#include <SDL_stdinc.h>

class Component {
public:
    // Constructor
    // (the lower the update order, the earlier the component updates)
    explicit Component(int updateOrder = 100);
    // Destructor
    virtual ~Component();
    // Update this component by delta time
    virtual void Update(float deltaTime);
    // Process input for this component (if needed)
    virtual void ProcessInput(const Uint8* keyState);
    // Debug draw for this component (if needed)
    virtual void DebugDraw(class Renderer* renderer);

    int GetUpdateOrder() const { return mUpdateOrder; }

    void SetEnabled(const bool enabled) { mIsEnabled = enabled; };
    bool IsEnabled() const { return mIsEnabled; };

protected:
    // Update order
    int mUpdateOrder;
    // Is component enabled
    bool mIsEnabled;
};
