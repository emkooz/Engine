// Every single include needed for the engine so that you wouldn't need to include over and over and over and over and over and over and over and over and over again
#ifndef INCLUDES
#define INCLUDES

#include <GL/glew.h>
#include <GL/glfw.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <SOIL.h>
#include <ft2build.h>
#include FT_FREETYPE_H

#include <oglft/OGLFT.h>

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
#include "Text.hpp"
#include "Engine.hpp"


static Engine Game(800 , 600);

static Cam Camera;
static Keys Key;
static ModelLoader obj;
static FTText Text;

// Create a pixmap font from a TrueType file.
static OGLFT::Monochrome* font;




#endif
