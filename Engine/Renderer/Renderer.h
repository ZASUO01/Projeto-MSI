//
// Created by pedro-souza on 28/04/2026.
//

#include <SDL2/SDL.h>
#include "Utils/Math.h"

class Renderer {
public:
    explicit Renderer(SDL_Window *window);
    ~Renderer() = default;

    bool Initialize(float width, float height);
    void Shutdown();

    static void Clear();
    void Draw() const;
    void Present() const;

private:
    static constexpr Vector4 CLEAR_COLOR{0.45f, 0.55f, 0.60f, 1.0f};

    SDL_Window *mWindow;
    SDL_GLContext mContext;

    float mScreenWidth;
    float mScreenHeight;
};
