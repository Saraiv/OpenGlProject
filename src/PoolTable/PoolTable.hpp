#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/ext.hpp>
#include <vector>
#include <GL/gl.h>
#include <iostream>
#include <math.h>

#include "../Shaders/Shaders.hpp"

using namespace std;
using namespace glm;

namespace Table{
    class PoolTable{
        public:
            void Draw(vector<vec3> model, mat4 mvp);
            void Render();
            vector<vec3> Model();
            GLuint Program();
        private:
            int verticesCount;
            float height = 3.0f;
            float width = 25.0f;
            float large = 35.0f;
            float heightOffset = 0.0f;

            float tableHeight = height / 2 + heightOffset;
            float tableWidth = width / 2;
            float tableLarge = large / 2;

            GLuint shader, VBO, VAO, program;
    };
}