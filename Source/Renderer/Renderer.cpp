//
// Created by pedro-souza on 17/04/2026.
//

#include "Renderer.h"

#include <ranges>
#include <GL/glew.h>

#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"

Renderer::Renderer(SDL_Window *window, const RendererMode renderMode)
: mModelsShader(nullptr)
, mWindow(window)
, mContext(nullptr)
, mScreenWidth(1024.0f)
, mScreenHeight(768.0f)
, mRenderMode(renderMode)
{}

bool Renderer::Initialize(const float width, const float height){
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
   SDL_Log("Failed to create OpenGL context.",SDL_GetError());
   return false;
 }

 // Initialize GLEW
 glewExperimental = GL_TRUE;
 if (glewInit() != GLEW_OK) {
  SDL_Log("Failed to initialize GLEW.");
  return false;
 }

 // Make sure we can create/compile shaders
 if (!LoadShaders()){
  SDL_Log("Failed to load shaders.");
  return false;
 }

 // Set the clear color to light blue
 glClearColor(0.45f, 0.55f, 0.60f, 1.0f);

 return true;
}

void Renderer::Shutdown(){
 UnloadData();

 mModelsShader->Unload();
 delete mModelsShader;
 mModelsShader = nullptr;

 SDL_GL_DeleteContext(mContext);
}

void Renderer::UnloadData(){
 // Destroy meshes
 for (const auto val: mMeshes | std::views::values){
  val->Unload();
  delete val;
 }
 mMeshes.clear();

 for (const auto val: mTextures | std::views::values) {
  val->Unload();
  delete val;
 }
 mTextures.clear();
}


void Renderer::Clear(){
 // Clear the color buffer
 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Draw() const {
 // Enable depth buffering/disable alpha blend
 glEnable(GL_DEPTH_TEST);
 glDisable(GL_BLEND);

 // Set the models shader active
 mModelsShader->SetActive();

 // Update view-projection matrix
 mModelsShader->SetMatrixUniform("viewProjection", mView * mProjection);

 // DRAW

 // Disable depth buffering
 glDisable(GL_DEPTH_TEST);

 // Enable alpha blending on the color buffer
 glEnable(GL_BLEND);
}

void Renderer::Present() const {
 // Swap the buffers
 SDL_GL_SwapWindow(mWindow);
}

Mesh* Renderer::GetMesh(const std::string& fileName){
 Mesh* m = nullptr;

 if (const auto iter = mMeshes.find(fileName); iter != mMeshes.end()){
  m = iter->second;
 }
 else{
  m = new Mesh();
  if (m->Load(fileName)){
   mMeshes.emplace(fileName, m);
   return m;
  }

  delete m;
  return nullptr;
 }

 return m;
}

Texture* Renderer::GetTexture(const std::string& fileName) {
 Texture* tex = nullptr;
 if (const auto iter = mTextures.find(fileName); iter != mTextures.end()){
  tex = iter->second;
 }
 else{
  tex = new Texture();

  if (tex->Load(fileName)){
   mTextures.emplace(fileName, tex);
   return tex;
  }

   delete tex;
   return nullptr;
 }
 return tex;
}

bool Renderer::LoadShaders(){
 // Create basic model shader
 mModelsShader = new Shader();
 if (!mModelsShader->Load("../Shaders/Models")){
  return false;
 }
 mModelsShader->SetActive();

 // Set the view-projection matrix
 mView = Matrix4::CreateLookAt(Vector3(2.0f, 2.0f, 5.0f), Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f));
 mProjection = Matrix4::CreatePerspectiveFOV(45.0f, mScreenWidth, mScreenHeight,0.1f, 100.0f);
 mModelsShader->SetMatrixUniform("viewProjection", mView * mProjection);

 return true;
}