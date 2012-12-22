#include "Includes.hpp"

glm::vec3 BezPoint (float t, glm::vec3 p0, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3);

static unsigned int Width = 800;
static unsigned int Height = 600;

// "//-" = disabled for testing.


int main() // TODO: Indexing. UPDATED TODO: Assimp does this, do text now.
{	
	bool CursorEnabled = true;
	bool PolygonMode = false;
	bool RenderPyro = true;
	
	Text.Init();
	
	std::vector <glm::vec3> vertices;
	std::vector <glm::vec2> uv , boxuv;
	std::vector <glm::vec3> boxv , boxn;
	glm::vec3 LightPos = glm::vec3(6.0f , 1.0f , -2.0f);
	std::vector <glm::vec3> pos;
	
	std::string FPS;
	float fFPS;
	std::ostringstream Convert;
	
	Camera.SetSpeed (10.0f);
	
		// Enable depth test
        glEnable(GL_DEPTH_TEST);
        // Accept fragment if it closer to the camera than the former one
        glDepthFunc(GL_LESS); 
        glEnable(GL_CULL_FACE);
	
	if (!obj.ObjUV ("obj/pyro.obj" , vertices , uv))
	{
		std::cout << "\n Pyro was unable to be loaded";
	}
	
	if (!obj.ObjNormal ("obj/suzanne.obj" , boxv , boxuv , boxn))
		std::cout << "\nSuzanne was unable to be loaded";
		
	
    
	float sx = 2.0f / Width;
	float sy = 2.0f / Height;
	Text.UseFont ("font.ttf");
	Text.SetPixelSize (48);
	
	GLuint tex;
	GLuint id = SOIL_load_OGL_texture("obj/pyro_red.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
	glGenTextures (1 , &tex);
	
	GLuint suzTex;
	GLuint sID = SOIL_load_OGL_texture ("obj/uvmap.DDS" , SOIL_LOAD_AUTO , SOIL_CREATE_NEW_ID , SOIL_FLAG_MIPMAPS);
	glGenTextures (1 , &suzTex);
	
	//GLuint sshader = Game.LoadShaders ("src/glsl/1.2/shadow.vert" , "src/glsl/1.2/shadow.frag");
	
	glm::vec3 cp0 = glm::vec3 (0.0f , 0.0f , -1.0f);
	glm::vec3 cp1 = glm::vec3 (0.0f , 1.0f , -1.0f);
	glm::vec3 cp2 = glm::vec3 (1.0f , 1.0f , -1.0f);
	glm::vec3 cp3 = glm::vec3 (1.0f , 0.0f , -1.0f);
	
	std::vector <glm::vec3> pline;
		//---------------------------------------Buffers----------------------------------------------------------------------------
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
	
	GLuint vboBox;
		glGenBuffers (1 , &vboBox);
		glBindBuffer (GL_ARRAY_BUFFER , vboBox);
			glBufferData(GL_ARRAY_BUFFER , boxv.size() * sizeof (glm::vec3) , &boxv[0] , GL_STATIC_DRAW);
	
	GLuint uvBox;
		glGenBuffers (1 , &uvBox);
		glBindBuffer (GL_ARRAY_BUFFER , uvBox);
			glBufferData (GL_ARRAY_BUFFER , boxuv.size() * sizeof (glm::vec2) , &boxuv[0] , GL_STATIC_DRAW);
	
	GLuint norBox;
		glGenBuffers (1 , &norBox);
		glBindBuffer (GL_ARRAY_BUFFER , norBox);
			glBufferData (GL_ARRAY_BUFFER , boxn.size() * sizeof (glm::vec3) , &boxn[0] , GL_STATIC_DRAW);
	//---------------------------------------------------------------------------------------------------------------------------
	
	/*GLuint sshadow = Game.LoadShaders ("src/glsl/1.2/shadow.vert" , "src/glsl/1.2/shadow.frag");
	glBindFragDataLocation (sshadow , 0 , "color");
	GLuint MatrixID = glGetUniformLocation(sshadow, "MVP");
    GLuint ViewMatrixID = glGetUniformLocation(sshadow, "V");
    GLuint ModelMatrixID = glGetUniformLocation(sshadow, "M");
	GLuint ShadowID  = glGetUniformLocation(sshadow, "myTextureSampler");
	glUseProgram(sshadow);
        GLuint LightID = glGetUniformLocation(sshadow, "LightPosition_worldspace");
    glUseProgram(0);*/
	 
	
	//GLuint shader = LoadShaders ("src/glsl/vert.vert" , "src/glsl/frag.frag");
	//GLuint TextureID  = glGetUniformLocation(shader, "texPyro");
	
	//glBindFragDataLocation (shader , 0 , "outColor");

	//GLuint MatrixID = glGetUniformLocation (shader , "MVP");
	
	
	glm::mat4 Model = glm::mat4 (1.0f);
	Model = glm::rotate (Model , 90.0f , glm::vec3 (1.0f , 0.0f , 0.0f));
	Model = glm::translate (Model , glm::vec3 (-5.0f , 5.0f , 0.0f));
	Model = glm::scale (Model , glm::vec3 (0.2f));
	
	glm::mat4 boxm = glm::mat4 (1.0f);
	boxm = glm::translate (boxm , glm::vec3 (6.0f , 0.0f , 0.0f));
	
	Camera.CameraInit(45.0f , Width , Height , Model);

	glEnable (GL_POINT_SMOOTH);

	float LastTime = glfwGetTime(); // (for deltatime)
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
	while (true)
	{
		float DeltaTime = glfwGetTime() - LastTime; // Deltatime init
		LastTime = glfwGetTime(); // update for deltatime
		
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
			
	if (RenderPyro == true)
	{		
		Model = glm::rotate (Model , 7.0f * DeltaTime ,  glm::vec3 (0.0f , 0.0f ,1.0f));
		Camera.UpdateCamera (DeltaTime , Model);
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
	}
		//}
		
		/*-glUseProgram (sshadow);
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &Camera.GetMVP()[0][0]);
        glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &boxm[0][0]);
        glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &Camera.GetView()[0][0]);
        glUniform3f(LightID, LightPos.x, LightPos.y, LightPos.z);
        // Bind our texture in Texture Unit 0
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, suzTex);
        // Set our "myTextureSampler" sampler to user Texture Unit 0
        glUniform1i(ShadowID, 0);
         // 1rst attribute buffer : vertices
                glEnableVertexAttribArray(0);
                glBindBuffer(GL_ARRAY_BUFFER, vboBox);
                glVertexAttribPointer(
                        0,                  // attribute
                        3,                  // size
                        GL_FLOAT,           // type
                        GL_FALSE,           // normalized?
                        0,                  // stride
                        (void*)0            // array buffer offset
                );

                // 2nd attribute buffer : UVs
                glEnableVertexAttribArray(1);
                glBindBuffer(GL_ARRAY_BUFFER, uvBox);
                glVertexAttribPointer(
                        1,                                // attribute
                        2,                                // size
                        GL_FLOAT,                         // type
                        GL_FALSE,                         // normalized?
                        0,                                // stride
                        (void*)0                          // array buffer offset
                );

                // 3rd attribute buffer : normals
                glEnableVertexAttribArray(2);
                glBindBuffer(GL_ARRAY_BUFFER, norBox);
                glVertexAttribPointer(
                        2,                                // attribute
                        3,                                // size
                        GL_FLOAT,                         // type
                        GL_FALSE,                         // normalized?
                        0,                                // stride
                        (void*)0                          // array buffer offset
                );

                // Draw the triangles !
                glDrawArrays(GL_TRIANGLES, 0, boxv.size() );

                glDisableVertexAttribArray(0);
                glDisableVertexAttribArray(1);
                glDisableVertexAttribArray(2);
                
                glUseProgram(0);*/

		
		for (int x = 0; x <= 4; x++)
		{
			float t = x / 5.0f;
			glm::vec3 point = BezPoint (t , cp0 , cp1 , cp2 , cp3);
			
			pline.push_back (point);
				glPointSize (10.0f);
				glColor3f (1.0f , 1.0f , 1.0f);
				
				glPushMatrix();
				  glTranslatef (30 , 0.0f , -5);
					glBegin (GL_POINTS); // Actual points for curve (change to line maybe?)
						glVertex3f (point.x , point.y , point.z);
					glEnd();
					
					glPointSize (15.0f); // Control points.
					glColor3f (1.0f , 0.0f , 0.0f);
						glBegin (GL_POINTS);
							glVertex3f (cp0.x , cp0.y , cp0.z);
							glVertex3f (cp1.x , cp1.y , cp1.z);
							glVertex3f (cp2.x , cp2.y , cp2.z);
							glVertex3f (cp3.x , cp3.y , cp3.z);
						glEnd();
					glColor3f (1.0f , 1.0f , 1.0f);
				glPopMatrix();
		}


		
		/*Camera.UpdateCamera (DeltaTime , boxm);
		glEnableClientState (GL_VERTEX_ARRAY);
		glBindBuffer (GL_ARRAY_BUFFER , vboBox);
		glVertexPointer (3 , GL_FLOAT , 0 , NULL);
		glEnableClientState (GL_TEXTURE_COORD_ARRAY);
		glBindBuffer (GL_ARRAY_BUFFER , uvBox);
		glTexCoordPointer (2 , GL_FLOAT , 0 , NULL);
		glEnable (GL_TEXTURE_2D);
		glBindTexture (GL_TEXTURE_2D , sID);
		glMatrixMode (GL_MODELVIEW);
		glLoadMatrixf (&Camera.GetMVP()[0][0]);
		glDrawArrays (GL_TRIANGLES , 0 , boxv.size());
		glDisableClientState (GL_VERTEX_ARRAY);*/
		
		Text.RenderText("test",
						-1 + 8 * sx,   1 - 50 * sy,   sx * 0.5, sy * 0.5);
		
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


glm::vec3 BezPoint (float t, glm::vec3 p0, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3)
{
	float u = 1 - t;
	float tt = t * t;
	float uu = u * u;
		float uuu = uu * u;
		float ttt = tt * t;
 
  glm::vec3 p = uuu * p0; //first term
  p += 3 * uu * t * p1; //second term
  p += 3 * u * tt * p2; //third term
  p += ttt * p3; //fourth term
 
  return p;
}
