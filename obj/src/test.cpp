#include "Includes.hpp"

GLuint LoadShaders (const char * vert, const char * frag);

Cam Camera;
Keys Key;
ModelLoader obj;

static unsigned int Width = 800;
static unsigned int Height = 600;

int main()
{
	
	//OpenGL Setup
	if (!glfwInit())
	{
		std::cout << "GLFW failed to initialize!\n";
		return 1;
	}
	glfwOpenWindow(Width,Height,0,0,0,0,0,0,GLFW_WINDOW);
	if (glewInit() != GLEW_OK)
	{
		std::cout << "GLEW failed to initialize!\n";
		return 1;
	}
	glfwSetWindowTitle("");
	glViewport(0,0,Width, Height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,0,0,0,0,100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClearColor(1,0,0,1);
	//OpenGL Setup end
	
	bool CursorEnabled = true;
	bool PolygonMode = false;
	
	std::vector <glm::vec3> vertices;
	std::vector <glm::vec2> uv;
	
	if (!obj.ObjUV ("obj/pyro.obj" , vertices , uv))
	{
		std::cout << "\n Pyro was unable to be loaded";
	}
	
	//vertices.push_back (glm::vec3 (0.0f , 1.0f , 0.0f));
	//vertices.push_back (glm::vec3 (-1.0f , -1.0f , 0.0f));
	//vertices.push_back (glm::vec3 (1.0f , -1.0f , 0.0f));
	
	GLuint PyroTex = SOIL_load_image ("obj/pyro_red.png" , &width , &height , 0 , SOIL_LOAD_RGB);;
	glGenTextures (1 , &PyroTex);
	GLuint TextureID  = glGetUniformLocation(programID, "texPyro");
	
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
	 
	 
	
	
	GLuint shader = LoadShaders ("src/glsl/vert.vert" , "src/glsl/frag.frag");
	
	glBindFragDataLocation (shader , 0 , "outColor");
	
	GLuint MatrixID = glGetUniformLocation (shader , "MVP");
	
	
	glm::mat4 Model = glm::mat4 (1.0f);
	Camera.CameraInit(45.0f , Width , Height , Model);
	
	float LastTime = glfwGetTime(); // (for deltatime)
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
	while (true)
	{
		float DeltaTime = glfwGetTime() - LastTime; // Deltatime init
		LastTime = glfwGetTime(); // update for deltatime

		
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
		glClear (GL_COLOR_BUFFER_BIT);
		
		glUseProgram (shader);
		
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &Camera.GetMVP()[0][0]);
	
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	GLint posAttrib = glGetAttribLocation( shader, "position" );
	glEnableVertexAttribArray( posAttrib );
	glVertexAttribPointer( posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0 );
	
	
	glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, texPyro);
                // Set our "myTextureSampler" sampler to user Texture Unit 0
                glUniform1i(TextureID, 0)
	
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


GLuint LoadShaders (const char * vertex_file_path,const char * fragment_file_path)
{
		 // Create the shaders
        GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
        GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

        // Read the Vertex Shader code from the file
        std::string VertexShaderCode;
        std::ifstream VertexShaderStream (vertex_file_path);
        if(VertexShaderStream.is_open()){
                std::string Line = "";
                while(getline(VertexShaderStream, Line))
                        VertexShaderCode += "\n" + Line;
                VertexShaderStream.close();
        }

        // Read the Fragment Shader code from the file
        std::string FragmentShaderCode;
        std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
        if(FragmentShaderStream.is_open()){
                std::string Line = "";
                while(getline(FragmentShaderStream, Line))
                        FragmentShaderCode += "\n" + Line;
                FragmentShaderStream.close();
        }



        GLint Result;
        int InfoLogLength;



        // Compile Vertex Shader
        printf("Compiling shader: %s\n", vertex_file_path);
        char const * VertexSourcePointer = VertexShaderCode.c_str();
        glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
        glCompileShader(VertexShaderID);

        // Check Vertex Shader
        glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
        glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
        std::vector<char> VertexShaderErrorMessage(InfoLogLength);
        glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
        fprintf(stdout, "%s\n", &VertexShaderErrorMessage[0]);
        
        if (Result == GL_FALSE)
        {
			std::cout << "Vertex shader was unable to compile!\n";
			return 0;
		}




        // Compile Fragment Shader
        printf("Compiling shader: %s\n", fragment_file_path);
        char const * FragmentSourcePointer = FragmentShaderCode.c_str();
        glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
        glCompileShader(FragmentShaderID);

        // Check Fragment Shader
        glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
        glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
        std::vector<char> FragmentShaderErrorMessage(InfoLogLength);
        glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
        fprintf(stdout, "%s\n", &FragmentShaderErrorMessage[0]);


		if (Result == GL_FALSE)
		{
			std::cout << "Fragment shader was unable to compile!\n";
			return 0;
		}



        // Link the program
        fprintf(stdout, "Linking program\n");
        GLuint ProgramID = glCreateProgram();
        glAttachShader(ProgramID, VertexShaderID);
        glAttachShader(ProgramID, FragmentShaderID);
        glLinkProgram(ProgramID);

        // Check the program
        glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
        glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
        std::vector<char> ProgramErrorMessage( std::max(InfoLogLength, int(1)) );
        glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
        fprintf(stdout, "%s\n", &ProgramErrorMessage[0]);
        
        if (Result == GL_FALSE)
        {
			std::cout << "Shaders were unable to link!\n";
			return 0;
		}


        glDeleteShader(VertexShaderID);
        glDeleteShader(FragmentShaderID);

        return ProgramID;
}
