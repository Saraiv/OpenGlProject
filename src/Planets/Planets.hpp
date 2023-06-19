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

namespace Planet{
    class Planets {
        public:
            void GetPointersId(GLuint shader, GLuint vertexId, GLuint normalsId, GLuint texturesId, GLuint textureId, int counter);
            void Read(const string fileName);
            void Material(const string fileName);
            void Texture(const string textureFile);
            void Send(void);
            void Draw(vec3 position, vec3 orientation, mat4 modelMatrix);
            ~Planets();
            vec3 ka, kd, ks;
            GLfloat ns;
        private:
            mat4 planet;
            float accumulatedRotationY = 0.0f, Ns, angle = 0.0f, ZOOM = 15.0f;
            
            GLuint  VAO, 
                    VBO[3],
                    shader,
                    textureName,
                    vertexId,
                    normalsId,
                    texturesId,
                    textureId;
            
            vector<vec3> vertex_positions;
            vector<vec2> vertex_textures_coords;
            vector<vec3> vertex_normals;

            int counter;
    };
}