#ifndef INCLUDES
#define INCLUDES

#include <GL/glew.h>
#include <GL/glfw.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <SOIL.h>


#include <FTGL/ftgl.h>

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


// Create a pixmap font from a TrueType file.
static FTGLPixmapFont font("font.ttf");



#endif
