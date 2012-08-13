#ifndef ENGINE
#define ENGINE

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
	void SetHeight(int h);
};

#endif
