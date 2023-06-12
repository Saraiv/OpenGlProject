#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>

#include "Camera/Camera.hpp"
#include "PoolTable/PoolTable.hpp"

#define WIDTH 800
#define HEIGHT 600

using namespace std;
using namespace glm;
using namespace Cam;
using namespace Table;

GLuint programTable;
void initTable(GLuint programTable);

int main(int, char**){
    GLFWwindow* window;
    Camera* cam;
    cam = cam->GetInstance();
    PoolTable pt;
    cam->InicializeCamera(45.0f, WIDTH, HEIGHT, vec3(50.0f, 20.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f));

    if(!glfwInit()) return -1;

    glewInit();
    
    initTable(pt.Program());
    pt.Render();

    window = glfwCreateWindow(800, 600, "Window", NULL, NULL);
    glfwMakeContextCurrent(window);

    while(!glfwWindowShouldClose(window)){
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        mat4 mvp = cam->projection * cam->view;

        pt.Draw(pt.Model(), mvp);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void initTable(GLuint programTable){
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    glUseProgram(programTable);
}