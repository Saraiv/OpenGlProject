#include "Camera.hpp"

using namespace Cam;

void Camera::InicializeCamera(float fov, float width, float height, vec3 position, vec3 target){
    zoom = 5.0f;
    this->position = position;
    this->position.z = zoom;
    this->target = target;
    vec3 camFront = position - target;
    vec3 camRight = cross(camFront, vec3(0.0f, 1.0f, 0.0f));
    vec3 worldUp = -cross(camFront, camRight);

    target = position - normalize(camFront);

    projection = perspective(radians(fov), width / height, 0.1f, 100.0f);
    view = lookAt(this->position, target, worldUp);
}

void Camera::Update(){
    view = lookAt(vec3(position.x, position.y, position.z), target, vec3(0.0f, 1.0f, 0.0f));
}

void Camera::mouseCallback(GLFWwindow* window, double xpos, double ypos){
    if(firstMouse){
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.5f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if(pitch > 90.0f)
        pitch = 90.0f;
    if(pitch < -90.0f)
        pitch = -90.0f;

    position.x = cos(radians(yaw)) * cos(radians(pitch)) * zoom;
    position.y = -sin(radians(pitch)) * zoom;
    position.z = sin(radians(yaw)) * cos(radians(pitch)) * zoom;
}

Camera* Camera::_instance = nullptr;

Camera* Camera::GetInstance(){
    return (!_instance) ? _instance = new Camera : _instance;
}