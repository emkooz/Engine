#include "Includes.hpp"

void Cam::CameraInit (float fov , int w , int h , glm::mat4 Model)
{
	FoV = fov;
	width = w;
	height = h;
	Speed = 25.0f;
	MouseSpeed = 0.005;
	
	Position = glm::vec3 (0.0 , 0.0 , 3.0);

	Projection = glm::perspective(FoV, (float)width / (float)height, 0.1f, 100.0f);
    View       = glm::lookAt(
                                                                Position,
                                                                glm::vec3(0,1,0),
                                                                glm::vec3(0,0,0)
                                                   );
   // Model      = glm::mat4(1.0f);
	MVP        = Projection * View * Model;
	
	// Set the mouse pos to the center so the camera doesn't start off at a different angle
	glfwSetMousePos (width / 2 , height / 2);
}

void Cam::UpdateCamera (float dt , glm::mat4 Model)
{
	LastMX = MouseX; LastMY = MouseY;
	glfwGetMousePos (&MouseX, &MouseY);


	HorizontalAngle +=  0.005 * (LastMX - MouseX );
    VerticalAngle   +=  0.005 * (LastMY - MouseY );
		

	if (glfwGetKey( 'W' ) == GLFW_PRESS)
		Position += Direction * dt * Speed;
	

	if (glfwGetKey( 'S' ) == GLFW_PRESS)
		Position -= Direction * dt * Speed;
	

	if (glfwGetKey( 'D' ) == GLFW_PRESS)
		Position += Right * dt * Speed;
	

	if (glfwGetKey( 'A' ) == GLFW_PRESS)
		Position -= Right * dt * Speed;
	

		 // Direction : Spherical coordinates to Cartesian coordinates conversion (stolen from opengl-tutorial.org don't kill me ok)
        Direction = glm::vec3(
                cos(VerticalAngle) * sin(HorizontalAngle), 
                sin(VerticalAngle),
                cos(VerticalAngle) * cos(HorizontalAngle)
        );
        
        // Right vector
        Right = glm::vec3(
                sin(HorizontalAngle - 3.14f/2.0f), 
                0,
                cos(HorizontalAngle - 3.14f/2.0f)
        );
        
        // Up vector
        Up = glm::cross( Right, Direction );

		View       = glm::lookAt(
                                                                Position,           // Camera is here
                                                                Position + Direction, // and looks here : at the same position, plus "direction"
                                                                Up                  // Head is up (set to 0,-1,0 to look upside-down)
                                                   );
        MVP        = Projection * View * Model;
}

glm::mat4 Cam::GetMVP()
{
	return MVP;
}

glm::mat4 Cam::GetView()
{
	return View;
}

glm::mat4 Cam::GetProjection()
{
	return Projection;
}

		float Cam::GetSpeed()
		{
			return Speed;
		}
		
		void Cam::SetSpeed(float sp)
		{
			Speed = sp;
		}
		
		float Cam::GetMouseSpeed()
		{
			return MouseSpeed;
		}
		
		void Cam::SetMouseSpeed(float sp)
		{
			MouseSpeed = sp;
		}

		float Cam::GetFoV()
		{
			return FoV;
		}
		
		void Cam::SetFov(float fov)
		{
			FoV = fov;
		}
