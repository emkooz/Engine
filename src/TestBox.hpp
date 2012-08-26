#ifndef TEST_BOX
#define TEST_BOX

#include "Includes.hpp"

class TestBox
{
	public:
	std::vector <glm::vec3> verts;
	glm::vec3 Pos;
	glm::mat4 Model;
	GLuint vbo;
	
	float velY, velX , gravity;
	
	bool jumping;
	
	TestBox();
	void Draw();
	void Translate (glm::vec3 space);
	void Update(float);
	
	glm::mat4 GetModel();
};

class TestBoxMain
{
	public:
	TestBox MBox;
	
	void Jump();
};

#endif
