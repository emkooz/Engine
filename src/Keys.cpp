#include "Keys.hpp"



void Keys::Init()
{
	for (int x = 0; x < 512; x++)
	{
		Pressed[x] = false;
		KeyMem[x] = false;

	}
}

bool Keys::SinglePress(int key) // IT WORKS!
{
	
	  if (glfwGetKey(key) && !Pressed[key])
			{
				  Pressed[key] = true;

				  return true;
			}
				
	  if (!glfwGetKey(key))
			{
				Pressed[key] = false;
				return false;
			}
			else
				return false;
}

bool Keys::RapidPress(int key)
{
	//glfwGetKey(key);    Not sure what to do with this yet but whatever, I GOT SINGLE PRESS TO WORK!

	return true;
}
