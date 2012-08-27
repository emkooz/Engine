#ifndef INCLUDES
#define INCLUDES

#include <GL/glew.h>
#include <GL/glfw.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <SOIL.h>
#include <ft2build.h>
#include FT_FREETYPE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <math.h>
#include <sstream>

#include "Camera.hpp"
#include "Keys.hpp"
#include "Model.hpp"
#include "Engine.hpp"


static Engine Game(800 , 600);

static Cam Camera;
static Keys Key;
static ModelLoader obj;

static FT_Library ft;


#endif
