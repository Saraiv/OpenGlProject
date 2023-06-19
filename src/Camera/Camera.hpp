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
            enum class Direction{
                FORWARD,
                BACKWARD,
                LEFT,
                RIGHT
            };
            mat4 view, projection;
            vec3 position, target, worldUp;
            double lastX, lastY, yaw, pitch;
            bool firstMouse;
            float zoom, angle;

            void mouseCallback(GLFWwindow* window, double xpos, double ypos);
            void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
            static Camera* GetInstance();
            void InicializeCamera(float fov, float width, float height, vec3 position, vec3 target);
            Camera(){
                lastX = 0.0f;
                lastY = 0.0f;
                yaw = 0.0f;
                pitch = 0.0f;
                firstMouse = true;
                zoom = 5.0f;
            }
            void Update();
            void Move(Direction direction, float speed, double deltaTime);
        private:
            static Camera* _instance;
            const float maxX = 100.0f, minX = -100.0f, maxY = 100.0f, minY = -100.0f, maxZ = 100.0f, minZ = -100.0f;
    };
}