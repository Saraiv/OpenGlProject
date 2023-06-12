#pragma once

#include <GLFW/glfw3.h>
#include <glm/ext.hpp>
#include <vector>
#include <GL/gl.h>
#include <iostream>
#include <math.h>

using namespace std;
using namespace glm;

namespace Cam{
    class Camera{
        public:
            mat4 view;
            mat4 projection;
            vec3 position;
            vec3 target;
            double lastX, lastY, yaw, pitch;
            bool firstMouse;
            float zoom, angle;

            void mouseCallback(GLFWwindow* window, double xpos, double ypos);
            void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
            static Camera* GetInstance();
            void InicializeCamera(float fov, float width, float height, vec3 position, vec3 target);
            Camera() {
                lastX = 0.0f;
                lastY = 0.0f;
                yaw = 0.0f;
                pitch = 0.0f;
                firstMouse = true;
                zoom = 5.0f;
            }
            void Update();
        private:
            static Camera* _instance;
    };
}