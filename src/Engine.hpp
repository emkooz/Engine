#ifndef ENGINE
#define ENGINE

#include "Includes.hpp"

class Engine
{
	private:
	int Width;
	int Height;
	
	public:
	Engine (int width , int height);
	
	int GetWidth();
	void SetWidth(int w);
	
	int GetHeight();
	void SetHight(int h);
};

#endif
