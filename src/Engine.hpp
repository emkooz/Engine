#ifndef ENGINE
#define ENGINE

#include "Includes.hpp"

class Engine
{
	private:
	int Width;
	int Height;
	
	public:
	Engine(int width, int height);
	GLuint LoadShaders(const char * vert , const char * frag);
};

#endif
