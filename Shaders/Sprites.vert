#version 330

layout (location = 0) in vec3 inPosition;

uniform mat4 uWorldTransform;
uniform mat4 uOrthoProj;

void main(){
    vec4 worldPos = uWorldTransform * vec4(inPosition, 1.0);
	gl_Position = uOrthoProj * worldPos;
}