//
// Created by pedro-souza on 28/04/2026.
//
#pragma once
#include <string>
#include <unordered_map>
#include <GL/glew.h>
#include "../Utils/Math.h"

/**
 * It contains metadata from a shader uniform variable.
 */
struct UniformInfo {
    GLint location;
    GLenum type;
};

class Shader {
public:
    Shader();
    ~Shader() = default;

    bool Load(const std::string &name);
    void Unload();

    void SetActive() const;

    GLint GetUniformLocation(const std::string &name) const;

    static void SetVectorUniform (GLint location, const Vector2& vector);
    static void SetVectorUniform (GLint location, const Vector3& vector);
    static void SetVectorUniform (GLint location, const Vector4& vector);
    void SetMatrixUniform(GLint location, const Matrix4& matrix) const;
    void SetFloatUniform(GLint location, float value) const;
    void SetTextureUniform(GLint location, int value) const;
private:
    void IntrospectUniforms();

    static bool CompileShader(const std::string &fileName, GLenum shaderType, GLuint &outShader);
    static bool IsCompiled(GLuint shader);
    [[nodiscard]] bool IsValidProgram() const;

    GLuint mVertexShader;
    GLuint mFragmentShader;
    GLuint mShaderProgram;

    std::unordered_map<std::string, UniformInfo> mUniforms;
 };