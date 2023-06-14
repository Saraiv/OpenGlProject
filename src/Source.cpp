#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>

#include "Camera/Camera.hpp"
#include "Planets/Planets.hpp"
#include "Shaders/Shaders.hpp"

#define WIDTH 800
#define HEIGHT 600

using namespace std;
using namespace glm;
using namespace Cam;
using namespace Planet;

vector<vec3> planetPosition{
    vec3(0.0f, 0.0f, 0.0f)
};
mat4 planetMatrix = mat4(1.0f);
double lastMouseX = 0, lastMouseY = 0;
bool isMouseDragging = false;
float zoomLevel = 1.0f, angle = 0.0f;
GLuint shader, vertexId, texturesId, normalsId, textureId;

void initPlanets();
void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);

int main(int, char**){
    GLFWwindow* window;
    Camera* cam;
    cam = cam->GetInstance();
    cam->InicializeCamera(45.0f, WIDTH, HEIGHT, vec3(50.0f, 20.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f));

    if(!glfwInit()) return -1;

    window = glfwCreateWindow(800, 600, "Planets", NULL, NULL);
    glfwMakeContextCurrent(window);

    glfwSetScrollCallback(window, ScrollCallback);

    glewExperimental = GL_TRUE;
    glewInit();

    initPlanets();
    Planets sun;
    sun.GetPointersId(shader, vertexId, normalsId, texturesId, textureId, 0);
    sun.Read("Sun.obj");
    sun.Send();

    while(!glfwWindowShouldClose(window)){
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        mat4 zoomMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(zoomLevel));

        glUseProgram(shader);
        sun.Draw(planetPosition[0], vec3(0.0f, 0.0f, 0.0f), planetMatrix * zoomMatrix);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void initPlanets(){
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

    ShaderInfo shaders[] = {
		{ GL_VERTEX_SHADER, planetVertPath.c_str() },
		{ GL_FRAGMENT_SHADER, planetFragPath.c_str() },
		{ GL_NONE, NULL }
	};

	shader = LoadShaders(shaders);
	glUseProgram(shader);

	vertexId = glGetProgramResourceLocation(shader, GL_PROGRAM_INPUT, "vertexPosition");
	texturesId = glGetProgramResourceLocation(shader, GL_PROGRAM_INPUT, "textureCoords");
	normalsId = glGetProgramResourceLocation(shader, GL_PROGRAM_INPUT, "vertexNormals");

	textureId = glGetProgramResourceLocation(shader, GL_UNIFORM, "textureSampler");
}

void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
	float zoomAmount = 0.1f;
	zoomLevel += yoffset * zoomAmount;

	float minZoom = 0.1f;
	float maxZoom = 10.0f;
	if (zoomLevel < minZoom)
		zoomLevel = minZoom;
	
	if (zoomLevel > maxZoom)
		zoomLevel = maxZoom;
}