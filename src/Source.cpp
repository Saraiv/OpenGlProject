#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>

#include "Camera/Camera.hpp"
#include "Planets/Planets.hpp"
#include "Shaders/Shaders.hpp"
#include "Lights/Lights.hpp"
#include "Background/Background.hpp"

#define WIDTH 800
#define HEIGHT 600

using namespace std;
using namespace glm;
using namespace Cam;
using namespace Planet;
using namespace Light;
using namespace BG;

vector<vec3> planetPosition{
    vec3(0.0f, 0.0f, 0.0f),
    vec3(5.0f, 0.0f, 0.0f),
    vec3(10.0f, 0.0f, 0.0f),
    vec3(15.0f, 0.0f, 0.0f),
    vec3(20.0f, 0.0f, 0.0f),
    vec3(25.0f, 0.0f, 0.0f),
    vec3(30.0f, 0.0f, 0.0f),
    vec3(35.0f, 0.0f, 0.0f),
    vec3(40.0f, 0.0f, 0.0f)
};

mat4 planetMatrix = mat4(1.0f);
float zoomLevel = 1.0f, angle = 0.0f;
GLuint shader, shaderBackground, vertexId, texturesId, normalsId, textureId, backgroundTextureId;
double lastMouseX = 0;
double lastMouseY = 0;
bool isMouseDragging = false;

void InitPlanets();
void GraphicsInfo();
void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
void MovePlanets(GLFWwindow* window, double xpos, double ypos);
void OnClickCallback(GLFWwindow* window, int button, int action, int mods);

int main(){
    GLFWwindow* window;
    Camera* cam;
    cam = cam->GetInstance();
    cam->InicializeCamera(45.0f, WIDTH, HEIGHT, vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f));

    if(!glfwInit()) return -1;

    window = glfwCreateWindow(800, 600, "Planets", NULL, NULL);
    if (window == NULL){ glfwTerminate(); return -1; }
    glfwMakeContextCurrent(window);

    GraphicsInfo();
    glfwSetScrollCallback(window, ScrollCallback);
    glfwSetCursorPosCallback(window, MovePlanets);
	glfwSetMouseButtonCallback(window, OnClickCallback);

    glewExperimental = GL_TRUE;
    glewInit();

    InitPlanets();
    Planets sun, mercury, venus, earth, mars, jupiter, saturn, uranus, neptune;
    sun.GetPointersId(shader, vertexId, normalsId, texturesId, textureId, 0);
    sun.Read("Sun.obj");
    sun.Send();
    Lights(&sun, shader);

    mercury.GetPointersId(shader, vertexId, normalsId, texturesId, textureId, 1);
    mercury.Read("Mercury.obj");
    mercury.Send();
    Lights(&mercury, shader);

    venus.GetPointersId(shader, vertexId, normalsId, texturesId, textureId, 2);
    venus.Read("Venus.obj");
    venus.Send();
    Lights(&venus, shader);

    earth.GetPointersId(shader, vertexId, normalsId, texturesId, textureId, 3);
    earth.Read("Earth.obj");
    earth.Send();
    Lights(&earth, shader);

    mars.GetPointersId(shader, vertexId, normalsId, texturesId, textureId, 4);
    mars.Read("Mars.obj");
    mars.Send();
    Lights(&mars, shader);

    jupiter.GetPointersId(shader, vertexId, normalsId, texturesId, textureId, 5);
    jupiter.Read("Jupiter.obj");
    jupiter.Send();
    Lights(&jupiter, shader);

    saturn.GetPointersId(shader, vertexId, normalsId, texturesId, textureId, 6);
    saturn.Read("Saturn.obj");
    saturn.Send();
    Lights(&saturn, shader);

    uranus.GetPointersId(shader, vertexId, normalsId, texturesId, textureId, 7);
    uranus.Read("Uranus.obj");
    uranus.Send();
    Lights(&uranus, shader);

    neptune.GetPointersId(shader, vertexId, normalsId, texturesId, textureId, 8);
    neptune.Read("Neptune.obj");
    neptune.Send();
    Lights(&neptune, shader);

    Background bg;
    // bg.GetPointersId(shaderBackground, backgroundTextureId);
    // bg.Texture();
    // bg.Send();

    while(!glfwWindowShouldClose(window)){
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        mat4 zoomMatrix = scale(mat4(1.0f), vec3(zoomLevel));

        glUseProgram(shader);
        
        // bg.Draw(vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f));
        sun.Draw(planetPosition[0], vec3(0.0f, 0.0f, 0.0f), planetMatrix * zoomMatrix);
        mercury.Draw(planetPosition[1], vec3(0.0f, 0.0f, 0.0f), planetMatrix * zoomMatrix);
        venus.Draw(planetPosition[2], vec3(0.0f, 0.0f, 0.0f), planetMatrix * zoomMatrix);
        earth.Draw(planetPosition[3], vec3(0.0f, 0.0f, 0.0f), planetMatrix * zoomMatrix);
        mars.Draw(planetPosition[4], vec3(0.0f, 0.0f, 0.0f), planetMatrix * zoomMatrix);
        jupiter.Draw(planetPosition[5], vec3(0.0f, 0.0f, 0.0f), planetMatrix * zoomMatrix);
        saturn.Draw(planetPosition[6], vec3(0.0f, 0.0f, 0.0f), planetMatrix * zoomMatrix);
        uranus.Draw(planetPosition[7], vec3(0.0f, 0.0f, 0.0f), planetMatrix * zoomMatrix);
        neptune.Draw(planetPosition[8], vec3(0.0f, 0.0f, 0.0f), planetMatrix * zoomMatrix);

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

	vertexId = glGetProgramResourceLocation(shader, GL_PROGRAM_INPUT, "VertexPosition");
	texturesId = glGetProgramResourceLocation(shader, GL_PROGRAM_INPUT, "TextureCoords");
	normalsId = glGetProgramResourceLocation(shader, GL_PROGRAM_INPUT, "VertexNormals");

	textureId = glGetProgramResourceLocation(shader, GL_UNIFORM, "TextureSampler");

    ShaderInfo shadersBackground[] = {
        { GL_VERTEX_SHADER, backgroundVertPath.c_str() },
        { GL_FRAGMENT_SHADER, backgroundFragPath.c_str() },
        { GL_NONE, NULL }
    };

    shaderBackground = LoadShaders(shadersBackground);
    glUseProgram(shaderBackground);

    backgroundTextureId = glGetUniformLocation(shaderBackground, "BackgroundTexture");
}

void GraphicsInfo(){
    const GLubyte* renderer = glGetString(GL_RENDERER);
    const GLubyte* vendor = glGetString(GL_VENDOR);
    const GLubyte* version = glGetString(GL_VERSION);
    const GLubyte* glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);

    cout << "Renderer: " << renderer << endl;
    cout << "Vendor: " << vendor << endl;
    cout << "OpenGL version: " << version << endl;
    cout << "GLSL version: " << glslVersion << endl;
}

void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset){
	float zoomAmount = 0.1f, minZoom = 0.1f,  maxZoom = 12.0f;;
	zoomLevel += yoffset * zoomAmount;

	if (zoomLevel < minZoom)
		zoomLevel = minZoom;
	
	if (zoomLevel > maxZoom)
		zoomLevel = maxZoom;
}

void MovePlanets(GLFWwindow* window, double xpos, double ypos){
	if (isMouseDragging){
		double deltaX = xpos - lastMouseX;
        double deltaY = ypos - lastMouseY;

		mat4 rotationX = rotate(mat4(1.0f), radians(static_cast<float>(deltaX)), vec3(0.0f, 1.0f, 0.0f));
		mat4 rotationY = rotate(mat4(1.0f), radians(static_cast<float>(deltaY)), vec3(1.0f, 0.0f, 0.0f));
        
		planetMatrix = rotationX * rotationY * planetMatrix;

		lastMouseX = xpos;
		lastMouseY = ypos;
	}
}

void OnClickCallback(GLFWwindow* window, int button, int action, int mods){
	if (button == GLFW_MOUSE_BUTTON_LEFT){
		if (action == GLFW_PRESS) {
			isMouseDragging = true;
			glfwGetCursorPos(window, &lastMouseX, &lastMouseY);
		}
		else if (action == GLFW_RELEASE){
			isMouseDragging = false;
		}
	}
}