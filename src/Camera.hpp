#ifndef CAMERA_HANDLER
#define CAMERA_HANDLER

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

		float GetSpeed();
		void SetSpeed();

		float GetMouseSpeed();
		void SetMouseSpeed();

		float GetFoV();
		void SetFov();

};
#endif
