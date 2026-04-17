#version 330

out vec4 outColor;
uniform vec3 uColor;

void main(){
    vec4 normUcolor = vec4(uColor, 1.0);
    outColor = normUcolor;
}