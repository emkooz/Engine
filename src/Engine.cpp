#include "Includes.hpp"

Engine::Engine (int width , int height)
{
	Width = width; Height = height;
	
	if (!glfwInit())
	{
		std::cout << "GLFW failed to initialize!\n";
	}
	glfwOpenWindow(Width,Height,0,0,0,0,32,0,GLFW_WINDOW);
	if (glewInit() != GLEW_OK)
	{
		std::cout << "GLEW failed to initialize!\n";
	}
	glfwSetWindowTitle("Engine");
	glViewport(0,0,Width, Height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,0,0,0,0,100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClearColor(1,0,0,1);
	
	glfwSwapInterval (0);
}

int Engine::GetWidth()
{
	return Width;
}

void Engine::SetWidth(int w)
{
	Width = w;
}



int Engine::GetHeight()
{
	return Height;
}

void Engine::SetHeight(int h)
{
	Height = h;
}
