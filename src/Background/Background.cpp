#include "Background.hpp"
using namespace BG;

#define STB_IMAGE_IMPLEMENTATION
#include "../../lib/stb/stb_image.h"

void Background::GetPointersId(GLuint shader, GLuint backgroundTextureId){
    this->shader = shader;
    this->backgroundTextureId = backgroundTextureId;
}

void Background::Texture(){
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture);

    int width, height, nChannels;
    for (unsigned int i = 0; i < textures.size(); ++i){
        unsigned char* image = stbi_load(textures[i].c_str(), &width, &height, &nChannels, 0);
        if (image){
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
            stbi_image_free(image);
        } else{
            std::cout << "Failed to load skybox texture: " << textures[i] << std::endl;
            stbi_image_free(image);
            return;
        }
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

void Background::Send(void){
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glBindVertexArray(0);
}

void Background::Draw(vec3 position, vec3 orientation){
    glDepthFunc(GL_LEQUAL);
    glUseProgram(shader);
    glBindVertexArray(VAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
    glUniform1i(backgroundTextureId, 0);
    glDrawArrays(GL_TRIANGLES, 0, 6 * 2 * 3);
    glBindVertexArray(0);
    glDepthFunc(GL_LESS);
}