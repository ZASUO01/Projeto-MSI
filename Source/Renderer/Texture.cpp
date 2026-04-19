//
// Created by pedro-souza on 18/04/2026.
//
#include "Texture.h"
#include <GL/glew.h>
#include <SDL_image.h>

Texture::Texture()
: mTextureID(0)
, mWidth(0)
, mHeight(0)
{}


bool Texture::Load(const std::string &fileName){
    SDL_Surface* loaded = IMG_Load(fileName.c_str());

    if (!loaded) {
        SDL_Log("Failed to load image %s: %s", fileName.c_str(), IMG_GetError());
        return false;
    }

    SDL_Surface *surface = SDL_ConvertSurfaceFormat(loaded, SDL_PIXELFORMAT_BGRA32, 0);

    if (!surface) {
        SDL_Log("Failed to convert surface format %s: %s", fileName.c_str(), IMG_GetError());
        return false;
    }


    mWidth = surface->w;
    mHeight = surface->h;

    // Generate a GL texture
    glGenTextures(1, &mTextureID);
    glBindTexture(GL_TEXTURE_2D, mTextureID);
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mWidth, mHeight,
                 0, GL_BGRA, GL_UNSIGNED_BYTE, surface->pixels);

    // Delete the SDL surface
    SDL_FreeSurface(surface);

    // Generate mipmaps for texture
    glGenerateMipmap(GL_TEXTURE_2D);

    // Enable linear filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return true;
}

void Texture::CreateFromSurface(const SDL_Surface* surface){
    mWidth = surface->w;
    mHeight = surface->h;

    // Generate a GL texture
    glGenTextures(1, &mTextureID);
    glBindTexture(GL_TEXTURE_2D, mTextureID);
    glPixelStorei(GL_UNPACK_ROW_LENGTH, surface->pitch / 4);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                 surface->pixels);

    // Use linear filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Texture::Unload() const {
	glDeleteTextures(1, &mTextureID);
}

void Texture::SetActive(const int index) const {
	glActiveTexture(GL_TEXTURE0 + index);
	glBindTexture(GL_TEXTURE_2D, mTextureID);
}