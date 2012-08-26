#include "TestBox.hpp"

TestBox::TestBox()
{
	verts.push_back (glm::vec3 (-1.0f , 1.0f , 0.0f));
	verts.push_back (glm::vec3 (-1.0f , -1.0f , 0.0f));
	verts.push_back (glm::vec3 (1.0f , -1.0f , 0.0f));
	verts.push_back (glm::vec3 (1.0f , 1.0f , 0.0f));
	
	
	glGenBuffers (1 , &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(glm::vec3), &verts[0], GL_STATIC_DRAW);
	
	Model = glm::mat4(1.0f);
	
	jumping = false;
	
	velY = 0.0f; velX = 0.0f; gravity = 5;
}

void TestBox::Draw()
{
	/*glEnableClientState (GL_VERTEX_ARRAY); 
			glBindBuffer (GL_ARRAY_BUFFER , vbo);
			glVertexPointer (3 , GL_FLOAT , 0 , NULL);

			glMatrixMode (GL_MODELVIEW);
			glLoadMatrixf (&_Cam.GetMVP()[0][0]);
		
			glDrawArrays (GL_QUADS , 0 , vert.size());
			
		
			glDisableClientState (GL_VERTEX_ARRAY);*/
}

void TestBox::Translate (glm::vec3 space)
{
	Model = glm::translate (glm::mat4() , Pos += space);
}

void TestBox::Update (float DeltaTime)
{
	
	if (jumping == true)
	{
		velY -= gravity * DeltaTime;
		Pos += glm::vec3 (velX , velY , 0.0f);
		
		if (Pos.y < 0.0f)
		{
			jumping = false;
			
			velY = 0.0f;
			velX = 0.0f;
		}
	}
	
	Model = glm::translate (glm::mat4() , Pos);	
	
}

glm::mat4 TestBox::GetModel()
{
	return Model;
}

void TestBoxMain::Jump()
{
	MBox.jumping = true;
	MBox.velY = 0.05f; MBox.velX = 0.05;
	
	
	//MBox.Translate (glm::vec3(0.0f , 1.0f , 0.0f));
}
