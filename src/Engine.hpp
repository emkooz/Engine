#ifndef ENGINE
#define ENGINE

class Engine
{
	private:
	int Width;
	int Height;
	
	public:
	Engine (int width , int height);
	
	void DrawPyro ();
	
	int GetWidth();
	void SetWidth(int w);
	
	int GetHeight();
	void SetHeight(int h);
	
	GLuint LoadShaders(const char * vert , const char * frag);
};

#endif
