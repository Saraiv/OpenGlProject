#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <vector>
#include <string>

using namespace std;
using namespace glm;

namespace Planet{
    class Planets {
        public:
            void GetPointersId(GLuint shader, GLuint coordsId, GLuint normalsId, GLuint texId, GLuint textureId, int counter);
            void Read(const string fileName);
            void Send(void);
            void Material(string fileName);
            void Texture(const string textureFile);
            void Draw(vec3 position, vec3 orientation, mat4 modelMatrix);
            vec3 ka, kd, ks;
            GLfloat ns;
        private:
            mat4 planet;
            float accumulatedRotationY = 0.0f, Ns, angle = 0.0f, ZOOM = 15.0f;
            
            GLuint  VAO, 
                    Buffers[3],
                    programa,
                    textureName,
                    NumVertices = 4034,
                    coordsId,
                    normalsId,
                    texId,
                    textureId;
            
            vector<vec3> vertex_positions;
            vector<vec2> vertex_textures_coords;
            vector<vec3> vertex_normals;

            int counter;
    };
}