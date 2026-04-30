//
// Created by pedro-souza on 28/04/2026.
//
#include "Shader.h"
#include <fstream>
#include <sstream>
#include <SDL_log.h>
#include <vector>

/**
 * Shader constructor. Initializes the shader ids as 0.
 */
Shader::Shader()
:mVertexShader(0)
,mFragmentShader(0)
,mShaderProgram(0)
{}

/**
* @brief Load shader of the specified name, excluding the .frag/.vert extension.
* @param name Name string to find the .vert and .frag files.
* @return True if the shader program loads successfully and false otherwise.
*/
bool Shader::Load(const std::string &name) {
    // Compile vertex and fragment shaders
    if (!CompileShader(name + ".vert", GL_VERTEX_SHADER, mVertexShader) ||
        !CompileShader(name + ".frag", GL_FRAGMENT_SHADER, mFragmentShader)) {
        return false;
    }

    // Now create a shader program that
    // links together the vertex/frag shaders
    mShaderProgram = glCreateProgram();
    glAttachShader(mShaderProgram, mVertexShader);
    glAttachShader(mShaderProgram, mFragmentShader);
    glLinkProgram(mShaderProgram);

    if (!IsValidProgram()) {
        return false;
    }

    IntrospectUniforms();
    return true;
}

void Shader::Unload() {
    glDeleteProgram(mVertexShader);
    glDeleteProgram(mFragmentShader);
    glDeleteProgram(mShaderProgram);

    mVertexShader = 0;
    mFragmentShader = 0;
    mShaderProgram = 0;

    mUniforms.clear();
}

/**
 * @brief Set this as the active shader program in the GPU.
 */
void Shader::SetActive() const {
    glUseProgram(mShaderProgram);
}

/**
 * @brief Sets a 2D Vector uniform.
 * @param location Uniform location in the shader.
 * @param vector 2D Vector to be set as the uniform value.
 */
void Shader::SetVectorUniform (const GLint location, const Vector2& vector) {
    glUniform2fv(location, 1, vector.GetAsFloatPtr());
}

/**
 * @brief Sets a 3D Vector uniform.
 * @param location Uniform location in the shader.
 * @param vector 3D Vector to be set as the uniform value.
 */
void SetVectorUniform (const GLint location, const Vector3& vector) {
    glUniform3fv(location, 1, vector.GetAsFloatPtr());
}

/**
 * @brief Sets a 4D Vector uniform.
 * @param location Uniform location in the shader.
 * @param vector 4D Vector to be set as the uniform value.
 */
void SetVectorUniform (const GLint location, const Vector4& vector) {
    glUniform4fv(location, 1, vector.GetAsFloatPtr());
}

/**
 * @brief Sets a matrix uniform.
 * @param location Uniform location in the shader.
 * @param matrix Matrix  to be set as the uniform value.
 */
void SetMatrixUniform(const GLint location, const Matrix4& matrix){
    glUniformMatrix4fv(location, 1, GL_FALSE, matrix.GetAsFloatPtr());
}

/**
 * @brief Sets a float uniform.
 * @param location Uniform location in the shader.
 * @param value float to be set as the uniform value.
 */
void SetFloatUniform(const GLint location, const float value) {
    glUniform1f(location, value);
}

/**
 * @brief Sets a texture uniform.
 * @param location Uniform location in the shader.
 * @param value id to be set as the uniform value.
 */
void SetTextureUniform(const GLint location, const int value) {
    glUniform1i(location, value);
}

void Shader::IntrospectUniforms() {
    mUniforms.clear();

    GLint numUniforms = 0;
    glGetProgramiv(mShaderProgram, GL_ACTIVE_UNIFORMS, &numUniforms);

    GLint maxNameLength = 0;
    glGetProgramiv(mShaderProgram, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxNameLength);

    std::vector<GLchar> nameBuffer(maxNameLength);

    for (GLint i = 0; i < numUniforms; ++i) {
        GLsizei length;
        GLint size;
        GLenum type;

        glGetActiveUniform(mShaderProgram, i, nameBuffer.size(), &length, &size, &type, nameBuffer.data());

        std::string name(nameBuffer.data(), length);

        const GLint location = glGetUniformLocation(mShaderProgram, name.c_str());

        mUniforms[name] = { location, type };
    }
}

bool Shader::CompileShader(const std::string &fileName, GLenum shaderType, GLuint &outShader) {
    // Open file
    if (std::ifstream shaderFile(fileName); shaderFile.is_open()){
        // Read all the text into a string
        std::stringstream shaderStream;
        shaderStream << shaderFile.rdbuf();
        std::string contents = shaderStream.str();
        const char* contentsChar = contents.c_str();

        // Create a shader of the specified type
        outShader = glCreateShader(shaderType);

        // Set the source characters and try to compile
        glShaderSource(outShader, 1, &contentsChar, nullptr);
        glCompileShader(outShader);

        if (!IsCompiled(outShader)){
            SDL_Log("[Shader] Failed to compile shader %s", fileName.c_str());
            return false;
        }
    }
    else{
        SDL_Log("[Shader] File not found: %s", fileName.c_str());
        return false;
    }

    return true;
}

bool Shader::IsCompiled(const GLuint shader) {
    GLint status = 0;

    // Query the compile status
    glGetProgramiv(shader, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE) {
        char buffer[512] = {};
        glGetProgramInfoLog(shader, 512, nullptr, buffer);
        SDL_Log("[Shader] GLSL Compile Failed:\n%s", buffer);
        return false;
    }
    return true;
}

bool Shader::IsValidProgram() const {
    GLint status = 0;

    // Query the link status
    glGetProgramiv(mShaderProgram, GL_LINK_STATUS, &status);
    if (status != GL_TRUE) {
        char buffer[512] = {};
        glGetProgramInfoLog(mShaderProgram, 512, nullptr, buffer);
        SDL_Log("[Shader] GLSL Link Status:\n%s", buffer);
        return false;
    }
    return true;
}
