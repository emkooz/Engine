#include <GL/glfw.h>

#ifndef KEYS
#define KEYS

class Keys
{
public:
	bool Pressed[512];
	bool KeyMem[512];

	void Init();
	bool SinglePress(int key);
	bool RapidPress(int key);
};

#endif
