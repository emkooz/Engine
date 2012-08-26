#include "Includes.hpp"

GLuint LoadShaders (const char * vert, const char * frag);

static unsigned int Width = 800;
static unsigned int Height = 600;

// "//-" = disabled for testing.


int main() // TODO: Indexing. UPDATED TODO: Assimp does this, do text now.
{	
	bool CursorEnabled = true;
	bool PolygonMode = false;
	
	std::vector <glm::vec3> vertices;
	std::vector <glm::vec2> uv;
	std::vector <glm::vec3> pos;
	
	std::string FPS;
	float fFPS;
	std::ostringstream Convert;
	
		// Enable depth test
        glEnable(GL_DEPTH_TEST);
        // Accept fragment if it closer to the camera than the former one
        glDepthFunc(GL_LESS); 
	
	if (!obj.ObjUV ("obj/pyro.obj" , vertices , uv))
	{
		std::cout << "\n Pyro was unable to be loaded";
	}
	
	int sx = Width / 2;
	int sy = Height / 2;
	Text.UseFont ("font.ttf");
	Text.SetPixelSize (48);
	
	GLuint tex;
	GLuint id = SOIL_load_OGL_texture("obj/pyro_red.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
	glGenTextures (1 , &tex);
	
	
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
	 
	
	//GLuint shader = LoadShaders ("src/glsl/vert.vert" , "src/glsl/frag.frag");
	//GLuint TextureID  = glGetUniformLocation(shader, "texPyro");
	
	//glBindFragDataLocation (shader , 0 , "outColor");

	//GLuint MatrixID = glGetUniformLocation (shader , "MVP");
	
	
	glm::mat4 Model = glm::mat4 (1.0f);
	Model = glm::rotate (Model , 90.0f , glm::vec3 (1.0f , 0.0f , 0.0f));
	Model = glm::scale (Model , glm::vec3 (0.2f));
	
	Camera.CameraInit(45.0f , Width , Height , Model);

	float LastTime = glfwGetTime(); // (for deltatime)
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
	while (true)
	{
		float DeltaTime = glfwGetTime() - LastTime; // Deltatime init
		LastTime = glfwGetTime(); // update for deltatime

		Camera.UpdateCamera (DeltaTime , Model);
		
		fFPS = 1 / DeltaTime;
		Convert << fFPS;
		FPS = Convert.str();
		
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
		
		if (Key.SinglePress (GLFW_KEY_SPACE))
		{
			
			
			std::cout << "jump" << std::flush;
		}
		
				
		//std::cout << std::endl << tb.MBox.Pos.x << std::flush;
		
		glClearColor (0.0f , 0.0f , 0.0f , 1.0f);
		glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		
		
	/*--	glEnableClientState (GL_VERTEX_ARRAY); 
			glBindBuffer GL_ARRAY_BUFFER , vbo);
			glVertexPointer (3 , GL_FLOAT , 0 , NULL);

			glMatrixMode (GL_MODELVIEW);
			glLoadMatrixf (&Camera.GetMVP()[0][0]);
		
			glDrawArrays (GL_TRIANGLES , 0 , verts.size());
			
		
			glDisableClientState (GL_VERTEX_ARRAY); --*/
		
		
		
		
	//	if (shader == NULL)
		//{
			
			glEnableClientState (GL_VERTEX_ARRAY); // Enable vert array
			glBindBuffer (GL_ARRAY_BUFFER , vbo); // bind the vbo
			glVertexPointer (3 , GL_FLOAT , 0 , NULL); // pointer in the vbo
			
			glEnableClientState (GL_TEXTURE_COORD_ARRAY); // tex array
		glBindBuffer (GL_ARRAY_BUFFER , uvbuf); // bind uv array
		glTexCoordPointer (2 , GL_FLOAT , 0 , NULL); // tex pointer

		glEnable (GL_TEXTURE_2D); // enable textures
		glBindTexture (GL_TEXTURE_2D , id); // bind the texture
		//glEnable(GL_BLEND);
	//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);*/
			glMatrixMode (GL_MODELVIEW); // go into the modelview matrix
			glLoadMatrixf (&Camera.GetMVP()[0][0]); // load the current MVP
		
			glDrawArrays (GL_TRIANGLES , 0 , vertices.size()); // draw everything
			
			glDisable (GL_TEXTURE_2D); // disable textures
	//	glDisable(GL_BLEND);
		
		glDisableClientState (GL_VERTEX_ARRAY); // disable arrays
			glDisableClientState (GL_TEXTURE_COORD_ARRAY); // disable arrays
		//}
		
		Text.RenderText("test",
						-1 + 8 * sx,   1 - 175 * sy,   sx * 0.5, sy * 0.5);
	
	
	
	
	
		
	/*	else
		{
			
		glUseProgram (shader);
		
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &Camera.GetMVP()[0][0]);
	
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	GLint posAttrib = glGetAttribLocation( shader, "position" );
	glEnableVertexAttribArray( posAttrib );
	glVertexAttribPointer( posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0 );
	
	
	glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, PyroTex]); // nvm
                glUniform1i(TextureID, 0);
	
	glBindBuffer(GL_ARRAY_BUFFER, uvbuf);
	GLint texAttrib = glGetAttribLocation( shader, "texPyro" );
	glEnableVertexAttribArray(texAttrib);
	glVertexAttribPointer( texAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0 );
		glActiveTexture (GL_TEXTURE0);
		glBindTexture (GL_TEXTURE_2D , PyroTex);

			image = SOIL_load_image ("obj/pyro_red.png" , &width , &height , 0 , SOIL_LOAD_RGB);
			glTexImage2D (GL_TEXTURE_2D , 0 , GL_RGB , width , height , 0 , GL_RGB , GL_UNSIGNED_BYTE , image);
			SOIL_free_image_data (image);

			glUniform1i (glGetUniformLocation (shader , "texPyro") , 0);
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	
    //glEnableVertexAttribArray(1);
   // glBindBuffer(GL_ARRAY_BUFFER,Buffers[1]);
   // glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,0,NULL);
    
   // glEnable(GL_BLEND);
   // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   // glEnable(GL_TEXTURE_2D);
    glDrawArrays(GL_TRIANGLES,0,vertices.size());
    //glDisable(GL_TEXTURE_2D);
   // glDisable(GL_BLEND);

    glDisableVertexAttribArray(posAttrib);
	glDisableVertexAttribArray(texAttrib);
   // glDisableVertexAttribArray(1);
	/*	
		// Send our transformation to the currently bound shader, 
        // in the "MVP" uniform
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &Camera.GetMVP()[0][0]);
		
			glBindBuffer (GL_ARRAY_BUFFER , vbo);
		GLint posAttrib = glGetAttribLocation (shader , "position");
		glEnableVertexAttribArray (posAttrib);
		glVertexAttribPointer (posAttrib , 3 , GL_FLOAT , GL_FALSE , 0 , 0);
		
	/*	glBindBuffer (GL_ARRAY_BUFFER , uvbuf);
		GLint texAttrib = glGetAttribLocation (shader , "texcoord");
		glEnableVertexAttribArray (texAttrib);
		glVertexAttribPointer (texAttrib , 2 , GL_FLOAT , GL_FALSE , 0 , 0);
		glActiveTexture (GL_TEXTURE0);
		glBindTexture (GL_TEXTURE_2D , PyroTex);
			
			image = SOIL_load_image ("obj/pyro-red.png" , &width , &height , 0 , SOIL_LOAD_RGB);
			glTexImage2D (GL_TEXTURE_2D , 0 , GL_RGB , width , height , 0 , GL_RGB , GL_UNSIGNED_BYTE , image);
			SOIL_free_image_data (image);
			
			glUniform1i (glGetUniformLocation (shader , "texPyro") , 0);
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
		*/
	//	glDrawArrays (GL_TRIANGLES , 0 , vertices.size());
	//	glDisableVertexAttribArray (posAttrib);
	//	glDisableVertexAttribArray (texAttrib);
	
		
			
		glfwSwapBuffers();
		
		
	
		if (glfwGetKey (GLFW_KEY_ESC) || !glfwGetWindowParam(GLFW_OPENED))
		{
			std::cout << "\nShutdown command. Exiting..." << std::flush;
			
			glDeleteBuffers (1 , &vbo);
			return 0;
		}
		
		
	}
	

}



