//
// Created by pedro-souza on 28/04/2026.
//

#include "Renderer.h"
#include "Texture.h"
#include <GL/glew.h>

Renderer::Renderer(SDL_Window *window)
:mWindow(window)
,mContext(nullptr)
,mScreenWidth(1024.0f)
, mScreenHeight(768.0f)
{}

bool Renderer::Initialize(const float width, const float height) {
    mScreenWidth = width;
    mScreenHeight = height;

    // Specify version 3.3 (core profile)
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    // Enable double buffering
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    // Force OpenGL to use hardware acceleration
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

    // Turn on vsync
    SDL_GL_SetSwapInterval(1);

    // Create an OpenGL context
    mContext = SDL_GL_CreateContext(mWindow);
    if (!mContext) {
        SDL_Log("[Renderer] Failed to create OpenGL context: %s",SDL_GetError());
        return false;
    }

    // Initialize GLEW
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        SDL_Log("[Renderer] Failed to initialize GLEW.");
        return false;
    }

    // Set the clear color to light blue
    glClearColor(CLEAR_COLOR.x, CLEAR_COLOR.y, CLEAR_COLOR.z, CLEAR_COLOR.w);

    return true;
}

void Renderer::Shutdown() {
    SDL_GL_DeleteContext(mContext);
}


void Renderer::Clear(){
    // Clear the color buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Draw() const {
    // TODO
}

void Renderer::Present() const {
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        SDL_Log("OpenGL Error antes do Swap: 0x%04X", err);
    }
    // Swap the buffers
    SDL_GL_SwapWindow(mWindow);
}