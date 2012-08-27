#include "Includes.hpp"

static unsigned int Width = 800;
static unsigned int Height = 600;

void render_text(const char *text, float x, float y, float sx, float sy);

struct point {GLfloat x; GLfloat y; GLfloat z; GLfloat w;};

//-------------------------------------------text stuff-----------------------------------------------------------------
	
	
	GLfloat white[4] = {1 , 1  , 1 , 0};
	GLuint TextShader = Game.LoadShaders ("src/glsl/1.2/text.vert" , "src/glsl/1.2/text.frag");
	GLint CoordAttrib = glGetAttribLocation (TextShader , "coord");
	GLint TexUniform = glGetUniformLocation (TextShader , "tex");
	GLint ColorUniform = glGetUniformLocation (TextShader , "color");
	GLuint Textvbo;
	
	
	
	
	
	FT_Face face;
	//----------------------------------------------------------------------------------------------------------------------

int main()
{	
	//text stuff
	if(FT_Init_FreeType(&ft)) 
	{
		fprintf(stderr, "Could not init freetype library\n");
		return 0;
	}
	
	if(FT_New_Face(ft, "font.ttf", 0, &face)) 
	{
		fprintf(stderr, "Could not open font\n");
		return 1;
	}
	glGenBuffers(1 , &Textvbo);
	glUniform4fv(ColorUniform , 1 , white);
	
	FT_Set_Pixel_Sizes (face , 0 , 48);
	FT_GlyphSlot g = face->glyph;
	//text stuff end
	
	bool CursorEnabled = true;
	bool PolygonMode = false;
	
	int width, height;
	
	float sx = 2.0f / Width; float sy = 2.0f / Height;
	
	std::vector <glm::vec3> vertices;
	std::vector <glm::vec2> uv;
	
	glEnable (GL_DEPTH_TEST);
	glDepthFunc (GL_LESS);
	
	if (!obj.ObjUV ("obj/pyro.obj" , vertices , uv))
	{
		std::cout << "\n Pyro was unable to be loaded";
	}
	
	//vertices.push_back (glm::vec3 (0.0f , 1.0f , 0.0f));
	//vertices.push_back (glm::vec3 (-1.0f , -1.0f , 0.0f));
	//vertices.push_back (glm::vec3 (1.0f , -1.0f , 0.0f));
	
	GLuint Tex;
	glGenTextures( 1, &Tex );
	
	unsigned char * PyroTex = SOIL_load_image( "obj/pyro_red.png", &width, &height, 0, SOIL_LOAD_RGB );
	
		// Create Vertex Array Object
	GLuint vao;
	glGenVertexArrays( 1, &vao );
	glBindVertexArray( vao );
	
	GLuint vbo;
	glGenBuffers (1 , &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
	
	GLuint uvbuf;
	glGenBuffers (1 , &uvbuf);
	glBindBuffer (GL_ARRAY_BUFFER, uvbuf);
	glBufferData(GL_ARRAY_BUFFER, uv.size() * sizeof(glm::vec2), &uv[0], GL_STATIC_DRAW);
	 
	 
	
	
	GLuint shader = Game.LoadShaders ("src/glsl/vert.vert" , "src/glsl/frag.frag");
	
	glBindFragDataLocation (shader , 0 , "outColor");
	
	GLuint MatrixID = glGetUniformLocation (shader , "MVP");
	
	
	
	
	
	std::ostringstream Convert;
	float  FPSf;
	std::string FPS;
	double FPStime = glfwGetTime();
	unsigned int uTime = (unsigned int)glfwGetTime();
	int counter = 0;
	
	
	
		GLuint TextureID  = glGetUniformLocation(shader, "texPyro");
	
	glm::mat4 Model = glm::mat4 (1.0f);
	Model = glm::rotate (Model , 90.0f , glm::vec3 (1.0f , 0.0f , 0.0f));
	Model = glm::scale (Model , glm::vec3 (0.5f));
	
	glm::mat4 textModel = glm::mat4 (1.0f);
		
	Camera.CameraInit(45.0f , Width , Height , Model);
	
	float LastTime = glfwGetTime(); // (for deltatime)
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
	while (true)
	{
		float DeltaTime = glfwGetTime() - LastTime; // Deltatime init
		LastTime = glfwGetTime(); // update for deltatime
		
		FPStime = glfwGetTime() - uTime;
		if (FPStime == 1 || FPStime > 1)
		{
			FPStime = 0;
			//FPSf = counter;
			counter = 0;
			uTime = (unsigned int)glfwGetTime();
			
			FPSf = 1.0f / DeltaTime;
			Convert << FPSf;
		    FPS = Convert.str();
		    
		    
		}
		else
			counter++;

		
		Camera.UpdateCamera (DeltaTime , Model);
		
		
		
		
		if (Key.SinglePress ('E'))
		{
			if (CursorEnabled == false)
			{
				glfwEnable (GLFW_MOUSE_CURSOR);
				CursorEnabled = true;
			}
			else
			{
				glfwDisable (GLFW_MOUSE_CURSOR);
				CursorEnabled = false;
			}
		}
		
		glClearColor (0.0f , 0.0f , 0.0f , 1.0f);
		glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
			glUseProgram (shader);
		
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &Camera.GetMVP()[0][0]); // Camera Uniform.------------------------------------------------------------
		glBindBuffer(GL_ARRAY_BUFFER, vbo); // Bind the Vertex Buffer																				|
			GLint posAttrib = glGetAttribLocation( shader, "position" ); // Get the "position" position from the shader.							|
			glEnableVertexAttribArray( posAttrib ); // Enable that "position".																		|
			glVertexAttribPointer( posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0 ); // Vertex pointer, points to what to render, how many, etc...			|
		
		glBindBuffer(GL_ARRAY_BUFFER, uvbuf); // Bind the UV buffer.																				|
			GLint texAttrib = glGetAttribLocation( shader, "texcoord" ); // shift this up    //"texcoord" location in the shader.					|
			glEnableVertexAttribArray( texAttrib ); // Enable "texcoord".																			|
			glVertexAttribPointer( texAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0 ); //Pointer for the data for the UV's, same style as vertices.			|
			glActiveTexture(GL_TEXTURE0); // Current texture slot.																					|------------  This is for drawing the Pyro.
                glBindTexture(GL_TEXTURE_2D, Tex); // Bind the texture																				|
                glUniform1i(TextureID, 0); // Set the sampler to slot 0.																			|
				glTexImage2D (GL_TEXTURE_2D , 0 , GL_RGB , width , height , 0 , GL_RGB , GL_UNSIGNED_BYTE , PyroTex); // Load the texture.			|

				glUniform1i (glGetUniformLocation (shader , "texPyro") , 0); // Sampler location.													|
				glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE ); // Extra options.											|
				glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE ); // Extra options.											|
				glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );	   // Extra options.											|
				glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );	   // Extra options.											|
				
		glDrawArrays(GL_TRIANGLES,0,vertices.size()); // Draw it.																					|
	glDisableVertexAttribArray(posAttrib); // Disable it.																							|
	glDisableVertexAttribArray(texAttrib); // Disable it.--------------------------------------------------------------------------------------------
	glUseProgram(0);
			
			glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			
			glUseProgram(TextShader);
	render_text("test",
              -1 + 8 * sx,   1 - 50 * sy,    sx, sy);
	glUseProgram(0);
		
	
		glfwSwapBuffers();

		if (glfwGetKey (GLFW_KEY_ESC) || !glfwGetWindowParam(GLFW_OPENED))
		{
			std::cout << "\nShutdown command. Exiting..." << std::flush;
			
			glDeleteBuffers (1 , &vbo);
			return 0;
		}
		
		
	}
	

}

void render_text(const char *text, float x, float y, float sx, float sy) {
	const char *p;
	FT_GlyphSlot g = face->glyph;

	/* Create a texture that will be used to hold one "glyph" */
	GLuint tex;
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &tex);
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
	glEnableVertexAttribArray(CoordAttrib);
	glBindBuffer(GL_ARRAY_BUFFER, Textvbo);
	glVertexAttribPointer(CoordAttrib, 4, GL_FLOAT, GL_FALSE, 0, 0);

	/* Loop through all characters */
	for(p = text; *p; p++) {
		/* Try to load and render the character */
		if(FT_Load_Char(face, *p, FT_LOAD_RENDER))
			continue;

		/* Upload the "bitmap", which contains an 8-bit grayscale image, as an alpha texture */
		glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, g->bitmap.width, g->bitmap.rows, 0, GL_ALPHA, GL_UNSIGNED_BYTE, g->bitmap.buffer);

		/* Calculate the vertex and texture coordinates */
		float x2 = x + g->bitmap_left * sx;
		float y2 = -y - g->bitmap_top * sy;
		float w = g->bitmap.width * sx;
		float h = g->bitmap.rows * sy;

		point box[4] = {
			{x2,	 -y2	, 0, 0},
			{x2 + w, -y2	, 1, 0},
			{x2,	 -y2 - h, 0, 1},
			{x2 + w, -y2 - h, 1, 1},
		};

		/* Draw the character on the screen */
		glBufferData(GL_ARRAY_BUFFER, sizeof box, box, GL_DYNAMIC_DRAW);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		/* Advance the cursor to the start of the next character */
		x += (g->advance.x >> 6) * sx;
		y += (g->advance.y >> 6) * sy;
	}

	glDisableVertexAttribArray(CoordAttrib);
	glDeleteTextures(1, &tex);
}
