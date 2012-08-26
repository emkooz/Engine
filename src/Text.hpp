#include "Includes.hpp"

class FTText
{
	public:
	
	FTText();
	bool UseFont (const char * fp);
	bool LoadTest();
	void RenderText (const char * , float x , float y , float SX , float SY);
	
	int GetPixelSize();
	void SetPixelSize(int size);
	
	private:
	FT_Library ft;
	FT_Face face;
	FT_GlyphSlot g;
	
	GLuint tex;
	unsigned char* id;
	
	GLuint vbo;
	GLuint uv;
	
	glm::mat4 Model;
	
	int PixelSize;
	int sx , sy;
};
