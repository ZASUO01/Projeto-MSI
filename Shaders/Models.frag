#version 330

in vec2 fragTextureCoord;

uniform sampler2D modelTexture;

out vec4 outColor;

void main(){
    outColor = texture(modelTexture, fragTextureCoord);
}