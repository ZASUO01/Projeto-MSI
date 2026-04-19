//
// Created by pedro-souza on 18/04/2026.
//
#pragma once
#include <string>
#include <SDL.h>

class Texture{
public:
    Texture();
    ~Texture() = default;

    bool Load(const std::string& fileName);
    void Unload() const;

    void CreateFromSurface(const SDL_Surface* surface);

    void SetActive(int index = 0) const;

    [[nodiscard]] int GetWidth() const { return mWidth; }
    [[nodiscard]] int GetHeight() const { return mHeight; }

    [[nodiscard]] unsigned int GetTextureID() const { return mTextureID; }

private:
    unsigned int mTextureID;
    int mWidth;
    int mHeight;
};