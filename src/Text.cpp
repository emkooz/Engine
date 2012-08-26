#include "Includes.hpp"

FTText::FTText()
{
	if(FT_Init_FreeType(&ft))
			std::cout << "\nError loading the FreeType library.";
			
	UseFont ("DejaVuSerif.ttf");
	
	g = face->glyph;
	
	Game.LoadShaders("src/glsl/1.2/text.vert" , "src/glsl/1.2/text.frag");
	
	glGenBuffers (1 , &vbo);
	glGenBuffers (1 , &uv);
	glGenTextures (1 , &tex);
	
	CoordUniform = glGetAttribLocation (shader , "coord");
	TexUniform   = glGetAttribLocation (shader , "tex"  );
	ColorUniform = glGetAttribLocation (shader , "color");
	
	Model = glm::mat4 (1.0f);

}


bool FTText::UseFont(const char * fp)
{
	if(FT_New_Face(ft, fp, 0, &face)) 
		{
			std::cout << "\nError loading the " << fp << "font.";
			return false;
		}
}

bool FTText::LoadTest()
{
	if(FT_Load_Char(face, 'X', FT_LOAD_RENDER))
		{
			std::cout << "\nCould not load the character 'X'";
			return false;
		}
}

void FTText::RenderText(const char *text, float x, float y, float SX, float SY) 
{
  const char *p;
	glUseProgram (shader);
	glEnable (GL_BLEND);
  	glBlendFunc (GL_SRC_ALPHA , GL_ONE_MINUS_SRC_ALPHA);
  	
  	GLfloat white[4] = {1 , 1 , 1 , 1};
  	SetColor(white);
  	
  	SetPixelSize(72);
  	
	glActiveTexture(GL_TEXTURE0);
	glGenTextures (1 , &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glUniform1i(TexUniform, 0);
	
    /* We require 1 byte alignment when uploading texture data */
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	
	/* Clamping to edges is important to prevent artifacts when scaling */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	
	/* Linear filtering usually looks best for text */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
 
	/* Set up the VBO for our vertex data */
	glEnableVertexAttribArray(CoordUniform);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(CoordUniform, 4, GL_FLOAT, GL_FALSE, 0, 0);
 
  for(p = text; *p; p++)
   {
    if(FT_Load_Char(face, *p, FT_LOAD_RENDER))
    {
		std::cout << "\nCould not load this text: " << text;
		continue;
	}
	
	
        id = g->bitmap.buffer;
 
    glTexImage2D(
      GL_TEXTURE_2D,
      0,
      GL_ALPHA,
      g->bitmap.width,
      g->bitmap.rows,
      0,
      GL_ALPHA,
      GL_UNSIGNED_BYTE,
      g->bitmap.buffer
    );
     
    float x2 = x + g->bitmap_left * SX;
    float y2 = -y - g->bitmap_top * SY;
    float w = g->bitmap.width * SX;
    float h = g->bitmap.rows * SY;
 
    GLfloat box1[2][4] = 
		{
			x2   , -y2    ,
			x2 + w, -y2    ,
			x2    , -y2 - h,
			x2 + w, -y2 - h
		};
   
    
    GLfloat box[4] = {
			(x2,	 -y2	, 0, 0),
			(x2 + w, -y2	, 1, 0),
			(x2,	 -y2 - h, 0, 1),
			(x2 + w, -y2 - h, 1, 1),
		};
	glBindBuffer (GL_ARRAY_BUFFER , vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof (box), box, GL_DYNAMIC_DRAW);
    glDrawArrays (GL_TRIANGLE_STRIP , 0 , 4);
  /*  glEnableClientState (GL_VERTEX_ARRAY); 
			glBindBuffer (GL_ARRAY_BUFFER , vbo);
			glVertexPointer (2 , GL_FLOAT , 0 , NULL);
			
		glEnableClientState (GL_TEXTURE_COORD_ARRAY);
		glBindBuffer (GL_ARRAY_BUFFER , uv);
		glTexCoordPointer (2 , GL_FLOAT , 0 , NULL);

		glEnable (GL_TEXTURE_2D);
		glBindTexture (GL_TEXTURE_2D , tex);
		//glEnable(GL_BLEND);
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glMatrixMode (GL_MODELVIEW);
			glLoadMatrixf (&Camera.GetMVP()[0][0]);
		
			glDrawArrays (GL_QUADS , 0 , 4);
			
			glDisable (GL_TEXTURE_2D);
		glDisable(GL_BLEND);
		
		glDisableClientState (GL_VERTEX_ARRAY);
			glDisableClientState (GL_TEXTURE_COORD_ARRAY);
	*/		
			
			 
 
    x += (g->advance.x >> 6) * SX;
    y += (g->advance.y >> 6) * SY;
  }
}

void FTText::SetPixelSize(int size)
{
	PixelSize = size;
	
	FT_Set_Pixel_Sizes(face, 0, PixelSize);
}

int FTText::GetPixelSize()
{
	return PixelSize;
}

void FTText::SetColor (GLfloat c[4])
{
	glUniform4fv (ColorUniform , 1 , c);
}
