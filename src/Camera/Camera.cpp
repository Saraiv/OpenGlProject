#include "Camera.hpp"

using namespace Cam;

void Camera::InicializeCamera(float fov, float width, float height, vec3 position, vec3 target){
    zoom = 5.0f;
    this->position = position;
    this->position.z = zoom;
    this->target = target;
    vec3 camFront = position - target;
    vec3 camRight = cross(camFront, vec3(0.0f, 1.0f, 0.0f));
    worldUp = -cross(camFront, camRight);

    target = position - normalize(camFront);

    projection = perspective(radians(fov), width / height, 0.1f, 100.0f);
    view = lookAt(this->position, target, worldUp);
}

void Camera::Update(){
    view = lookAt(vec3(position.x, position.y, position.z), target, vec3(0.0f, 1.0f, 0.0f));
}

void Camera::Move(Direction direction, float speed, double deltaTime){
    vec3 cameraFront = normalize(target - position);
    vec3 cameraRight = normalize(cross(cameraFront, worldUp));
    vec3 cameraUp = cross(cameraRight, cameraFront);

    float velocity = speed * deltaTime;

    if (direction == Direction::FORWARD){
        position += cameraFront * velocity;
    }
    else if (direction == Direction::BACKWARD){
        position -= cameraFront * velocity;
    }
    else if (direction == Direction::LEFT){
        position -= cameraRight * velocity;
    }
    else if (direction == Direction::RIGHT){
        position += cameraRight * velocity;
    }

    position.x = glm::clamp(position.x, minX, maxX);
    position.y = glm::clamp(position.y, minY, maxY);
    position.z = glm::clamp(position.z, minZ, maxZ);

    view = lookAt(position, target, worldUp);
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