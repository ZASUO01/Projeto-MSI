//
// Created by pedro-souza on 17/04/2026.
//
#pragma once

#include <string>
#include <unordered_map>
#include <SDL2/SDL.h>

#include "../Utils/Math.h"

enum class RendererMode{
    TRIANGLES,
    LINES
};

class Renderer{
public:
    explicit Renderer(SDL_Window* window, RendererMode renderMode);
    ~Renderer() = default;

    bool Initialize(float width, float height);
    void Shutdown();
    void UnloadData();

    static void Clear();
    void Draw() const;
    void Present() const;

    class Mesh* GetMesh(const std::string& fileName);
    class Texture* GetTexture(const std::string& fileName);

    void SetViewMatrix(const Matrix4& view) { mView = view; }
    void SetProjectionMatrix(const Matrix4& proj) { mProjection = proj; }

private:
    bool LoadShaders();

    static constexpr Vector4 CLEAR_COLOR{0.45f, 0.55f, 0.60f, 1.0f};

    // Shaders
    class Shader* mModelsShader;

    // Window and OpenGL context
    SDL_Window* mWindow;
    SDL_GLContext mContext;

    // Matrix for shaders
    Matrix4 mView;
    Matrix4 mProjection;

    // Maps of loaded resources
    std::unordered_map<std::string, Mesh*> mMeshes;
    std::unordered_map<std::string, Texture*> mTextures;

    // Width/height of screem
    float mScreenWidth;
    float mScreenHeight;

    RendererMode mRenderMode;
};