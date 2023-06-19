#version 440 core

in vec3 vTexCoords;

out vec4 FragColor;

uniform samplerCube BackgroundTexture;

void main(){
    FragColor = texture(BackgroundTexture, vTexCoords);
}