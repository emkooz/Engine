#ifndef CAMERA_HANDLER
#define CAMERA_HANDLER

//#include "Includes.hpp"

class Cam
{

	private:	
		glm::mat4 Projection, View, MVP;

		int MouseX , MouseY, LastMX, LastMY;
		float HorizontalAngle;
		float VerticalAngle;
		glm::vec3 Direction, Right, Up , Position;
		float Speed;
		float MouseSpeed;
		float FoV;
		int width;
		int height;

	public:
		void CameraInit(float fov , int w , int h , glm::mat4 Model);
		void UpdateCamera(float dt , glm::mat4 Model);

		glm::mat4 GetMVP();
		glm::mat4 GetView();
		glm::mat4 GetProjection();

		float GetSpeed();
		void SetSpeed(float);

		float GetMouseSpeed();
		void SetMouseSpeed(float);

		float GetFoV();
		void SetFov(float);

};
#endif
