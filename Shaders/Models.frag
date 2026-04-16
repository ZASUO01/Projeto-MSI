#version 330

in vec2 fragTextureCoord;

uniform vec3 modelColor;
uniform sampler2D modelTexture;

out vec4 outColor;

void main(){
    outColor = vec4(modelColor, 1.0);

    // future usage
    // outColor = texture(uTexture, fragTexCoord);
}