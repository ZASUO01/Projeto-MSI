#version 330

uniform mat4 modelTransform;
uniform mat4 viewProjection;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inTextureCoord;

out vec2 fragTextureCoord;

void main(){
    vec4 pos = vec4(inPosition, 1.0);
    gl_Position = viewProjection * modelTransform * pos;
    fragTextureCoord = inTextureCoord;
}