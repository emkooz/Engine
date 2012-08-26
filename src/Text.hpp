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
	
	void SetColor(GLfloat c[4]);
	
	private:
	FT_Library ft;
	FT_Face face;
	FT_GlyphSlot g;
	
	GLuint tex;
	unsigned char* id;
	
	GLuint vbo;
	GLuint uv;
	
	GLuint shader;	
	GLint CoordUniform;
	GLint TexUniform;
	GLint ColorUniform;
	//GLfloat color[4];
	
	glm::mat4 Model;
	
	int PixelSize;
	int sx , sy;
};
