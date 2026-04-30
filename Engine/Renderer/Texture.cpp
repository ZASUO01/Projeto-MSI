//
// Created by pedro-souza on 28/04/2026.
//

#include "Texture.h"
#include <SDL_image.h>
#include <GL/glew.h>

/**
 * @brief Constructor initializes texture params.
 */
Texture::Texture()
: mTextureID(0)
, mWidth(0)
, mHeight(0)
{}

/**
 * @brief Tries to load a texture from a file and set it to the GPU.
 * @param fileName The path to the PNG texture file.
 * @return True if it loads successfully and false otherwise.
 */
bool Texture::Load(const std::string &fileName){
    SDL_Surface* loaded = IMG_Load(fileName.c_str());

    if (!loaded) {
        SDL_Log("[Texture] Failed to load image %s: %s", fileName.c_str(), IMG_GetError());
        return false;
    }

    SDL_Surface *surface = SDL_ConvertSurfaceFormat(loaded, SDL_PIXELFORMAT_ABGR8888, 0);
    SDL_FreeSurface(loaded);

    if (!surface) {
        SDL_Log("[Texture] Failed to convert surface format %s: %s", fileName.c_str(), IMG_GetError());
        return false;
    }

    mWidth = surface->w;
    mHeight = surface->h;

    // Generate a GL texture
    glGenTextures(1, &mTextureID);
    glBindTexture(GL_TEXTURE_2D, mTextureID);
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mWidth, mHeight,
                 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);

    // Delete the SDL surface
    SDL_FreeSurface(surface);

    // Generate mipmaps for texture
    glGenerateMipmap(GL_TEXTURE_2D);

    // Enable linear filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    if (GLEW_EXT_texture_filter_anisotropic) {
        GLfloat largest;
        glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &largest);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, largest);
    }

    return true;
}

/**
 * @brief It tries to load the texture in GPU from a SDL2 surface instead of a file.
 * @param surface A SDL2 surface object.
 */
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

/**
 * Removes the texture data from the GPU.
 */
void Texture::Unload() const {
    glDeleteTextures(1, &mTextureID);
}

/**
 * @brief Sets the texture at index as active in the GPU.
 * @param index The texture index in the GPU that must be activated.
 */
void Texture::SetActive(const int index) const {
    glActiveTexture(GL_TEXTURE0 + index);
    glBindTexture(GL_TEXTURE_2D, mTextureID);
}