#pragma once
#include <GL/glew.h>
#include "../Shaders/Shaders.hpp"
#include "../Planets/Planets.hpp"
#include "../Camera/Camera.hpp"

using namespace std;
using namespace glm;
using namespace Planet;
using namespace Cam;

namespace Light{
    void Lights(Planets* planets, GLuint shader);
}