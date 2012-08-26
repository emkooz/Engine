// Every single include needed for the engine so that you wouldn't need to include over and over and over and over and over and over and over and over and over again
#ifndef INCLUDES
#define INCLUDES

//External libraries.
#include <GL/glew.h>
#include <GL/glfw.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <SOIL.h>
#include <ft2build.h>
#include FT_FREETYPE_H

//Standard libraries.
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <math.h>
#include <sstream>

//Classes/Namespaces.
#include "Camera.hpp"
#include "Keys.hpp"
#include "Model.hpp"
#include "Text.hpp"
#include "Engine.hpp"

//Global classes.
static Engine Game(800 , 600); // Game class, init's everything and handles window stuff.

static Cam Camera; // Camera class.
static Keys Key; // Key input handling class.
static ModelLoader obj; // Model loading class **TEMPORARY**
static FTText Text; // Text class (not working yet fffff)

#endif
