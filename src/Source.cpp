#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>

#include "Camera/Camera.hpp"
#include "Planets/Planets.hpp"
#include "Shaders/Shaders.hpp"
#include "Lights/Lights.hpp"

#define WIDTH 800
#define HEIGHT 600

using namespace std;
using namespace glm;
using namespace Cam;
using namespace Planet;
using namespace Light;

vector<vec3> planetPosition{
    vec3(0.0f, 0.0f, 0.0f)
};
mat4 planetMatrix = mat4(1.0f);
float zoomLevel = 1.0f, angle = 0.0f;
GLuint shader, vertexId, texturesId, normalsId, textureId;

void InitPlanets();
void GraphicsInfo();
void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);

int main(int, char**){
    GLFWwindow* window;
    Camera* cam;
    cam = cam->GetInstance();
    cam->InicializeCamera(45.0f, WIDTH, HEIGHT, vec3(50.0f, 20.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f));

    if(!glfwInit()) return -1;

    window = glfwCreateWindow(800, 600, "Planets", NULL, NULL);
    if (window == NULL){ glfwTerminate(); return -1; }
    glfwMakeContextCurrent(window);

    GraphicsInfo();
    glfwSetScrollCallback(window, ScrollCallback);

    glewExperimental = GL_TRUE;
    glewInit();

    InitPlanets();
    Planets sun;
    sun.GetPointersId(shader, vertexId, normalsId, texturesId, textureId, 0);
    sun.Read("Sun.obj");
    sun.Send();
    Lights(&sun, shader);

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

void InitPlanets(){
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
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

    cout << "shader main: " << shader << endl;
    cout << "vertex id main: " << vertexId << endl;
    cout << "textures id main: " << texturesId << endl;
    cout << "normals id main: " << normalsId << endl;
    cout << "texture id main: " << textureId << endl;
}

void GraphicsInfo(){
    const GLubyte* renderer = glGetString(GL_RENDERER);
    const GLubyte* vendor = glGetString(GL_VENDOR);
    const GLubyte* version = glGetString(GL_VERSION);
    const GLubyte* glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);

    std::cout << "Renderer: " << renderer << std::endl;
    std::cout << "Vendor: " << vendor << std::endl;
    std::cout << "OpenGL version: " << version << std::endl;
    std::cout << "GLSL version: " << glslVersion << std::endl;
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