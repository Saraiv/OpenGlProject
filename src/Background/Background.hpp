#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "../Camera/Camera.hpp"
#include "../Constants/Constants.hpp"

using namespace std;
using namespace glm;
using namespace Cam;
using namespace Constants;

namespace BG{
    class Background{
        public:
            void GetPointersId(GLuint shader, GLuint backgroundTextureId);
            void Texture();
            void Send(void);
            void Draw(vec3 position, vec3 orientation);
            ~Background();
        private:
            GLuint VAO, VBO, texture, shader, backgroundTextureId;
            vector<string> textures = {
                imagesPath + "Stars.jpg", imagesPath + "StarsMilkyWay.jpg", imagesPath + "Stars.jpg",
                imagesPath + "StarsMilkyWay.jpg", imagesPath + "Stars.jpg", imagesPath + "StarsMilkyWay.jpg"
            };
            float vertex[6 * 2 * 3 * 3] = {
                // Front face
                -60.0f,  60.0f, -60.0f,
                -60.0f, -60.0f, -60.0f,
                60.0f, -60.0f, -60.0f,
                60.0f, -60.0f, -60.0f,
                60.0f,  60.0f, -60.0f,
                -60.0f,  60.0f, -60.0f,

                // Back face
                60.0f, -60.0f,  60.0f,
                -60.0f, -60.0f,  60.0f,
                -60.0f,  60.0f,  60.0f,
                -60.0f,  60.0f,  60.0f,
                60.0f,  60.0f,  60.0f,
                60.0f, -60.0f,  60.0f,

                // Left face
                -60.0f, -60.0f,  60.0f,
                -60.0f, -60.0f, -60.0f,
                -60.0f,  60.0f, -60.0f,
                -60.0f,  60.0f, -60.0f,
                -60.0f,  60.0f,  60.0f,
                -60.0f, -60.0f,  60.0f,

                // Right face
                60.0f, -60.0f, -60.0f,
                60.0f, -60.0f,  60.0f,
                60.0f,  60.0f,  60.0f,
                60.0f,  60.0f,  60.0f,
                60.0f,  60.0f, -60.0f,
                60.0f, -60.0f, -60.0f,

                // Top face
                -60.0f,  60.0f,  60.0f,
                -60.0f,  60.0f, -60.0f,
                60.0f,  60.0f, -60.0f,
                60.0f,  60.0f, -60.0f,
                60.0f,  60.0f,  60.0f,
                -60.0f,  60.0f,  60.0f,

                // Bottom face
                -60.0f, -60.0f, -60.0f,
                -60.0f, -60.0f,  60.0f,
                60.0f, -60.0f, -60.0f,
                60.0f, -60.0f, -60.0f,
                -60.0f, -60.0f,  60.0f,
                60.0f, -60.0f,  60.0f
            };
    };
}