/******************************************************************************/
/*!
\file	FirstPersonCamera.cpp
\author Team NoticeMeSenpai
\brief
Camera funtions that calculate and return the latest position (& facing direction) of the camera
*/
/******************************************************************************/
#include "FirstPersonCamera.h"
#include "Application.h"
#include "Mtx44.h"
#include "GLFW\glfw3.h"
#include <vector>
#include "MyMath.h"

/******************************************************************************/
/*!
\brief	FPScamera default constructor
*/
/******************************************************************************/
FPSCamera::FPSCamera()
{
}

/******************************************************************************/
/*!
\brief	FPScamera default destructor
*/
/******************************************************************************/
FPSCamera::~FPSCamera()
{
}

/******************************************************************************/
/*!
\brief	FPScamera default constructor

\param	pos
	position vector3
\param	target
	target vector3
\param	up
	up vector3
*/
/******************************************************************************/
void FPSCamera::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
{
	this->position = defaultPosition = pos;
	this->target = defaultTarget = target;
	Vector3 view = (target - position).Normalized();
    Vector3 right = view.Cross(up).Normalized();
	right.y = 0;
    right.Normalize();
	this->up = defaultUp = right.Cross(view).Normalized();
    sensitivity = 0.05f;
    theta = -1;
    phi = -1;
}

/******************************************************************************/
/*!
\brief	Maths power function

\param	x
    x value

\param y
    exponent value
*/
/******************************************************************************/
int power (int x, int y)
{
    if (y == 0)
    {
        return 1;
    }

    else
    {
        return x * power(x, y-1);
    }
}

/******************************************************************************/
/*!
\brief	Yaw is negative when facing opposite of east direction

\param	y
    camera yaw value

\param a
    camera east value
*/
/******************************************************************************/
void Yaw(float &y, float a)
{
    if (a >= 0)
    {
        y*=(-1);
    }

    else
    {
        y*=(1);
    }
}

/******************************************************************************/
/*!
\brief	MAIN FPScamera Update function

\param	dt
    deltatime value
*/
/******************************************************************************/
void FPSCamera::Update(double dt)
{
	UpdateLooking_Mouse(dt);
    UpdateLooking_KeyB(dt);
    UpdateMovement(dt);

    // calculate the pitch
    pitch = (target.y - position.y) / (target.x - position.x);
    pitch = Math::RadianToDegree(atan(pitch));

    // calculate the yaw
    float a = sqrt(((target.z - position.z) * (target.z - position.z)) + ((target.x - position.x) * (target.x - position.x)));
    yaw = (target.z - position.z) / a;
    yaw = Math::RadianToDegree(acos(yaw));

    // north 
    north = (target.z - position.z) / a;
    north = Math::RadianToDegree(asin(north));

    // east
    east = (target.x - position.x) / a;
    east = Math::RadianToDegree(asin(east));

    Yaw(yaw, east);
}

/******************************************************************************/
/*!
\brief	Helper FPScamera Update function, For W A S D (movement of the camera)

\param	dt
    deltatime value
*/
/******************************************************************************/
void FPSCamera::UpdateMovement(double dt)
{
    float CAMERA_SPEED = 100.f;

    Vector3 vec = target - position;
    float magnitude = vec.Length();
    Vector3 UnitVec(vec.x / magnitude, vec.y / magnitude, vec.z/magnitude);

    if(Application::IsKeyPressed('W'))
    {
        position += UnitVec * (float)(CAMERA_SPEED * dt);
        target += UnitVec * (float)(CAMERA_SPEED * dt);
    }

    if(Application::IsKeyPressed('S'))
    {
        position -= UnitVec * (float)(CAMERA_SPEED * dt);
        target -= UnitVec * (float)(CAMERA_SPEED * dt);
    }


    Vector3 view2 = (target - position).Normalized();        
    Vector3 vec2 = view2.Cross(up); 
    float magnitude2 = vec2.Length();

    Vector3 UnitVec2(vec2.x / magnitude2, vec2.y / magnitude2, vec2.z/magnitude2);

    if(Application::IsKeyPressed('D'))
    {           

        position += UnitVec2 * (float)(CAMERA_SPEED * dt);
        target += UnitVec2 * (float)(CAMERA_SPEED * dt);
    }

    if(Application::IsKeyPressed('A'))
    {
        position -= UnitVec2 * (float)(CAMERA_SPEED * dt);
        target -= UnitVec2 * (float)(CAMERA_SPEED * dt);
    }
    
}

/******************************************************************************/
/*!
\brief	Helper FPScamera Update function, For viewing up down left right (mouse)

\param	dt
    deltatime value
*/
/******************************************************************************/
void FPSCamera::UpdateLooking_Mouse(double dt)
{
    float CAMERA_SPEED = 400.f;
    Mtx44 rotation;
    rotation.SetToIdentity();

    // mouse control
    GLFWwindow* glfwGetCurrentContext(void);
    glfwGetCursorPos(glfwGetCurrentContext(), &px, &py);

    horizMovement = (1000 / 2.0f - static_cast<float>(px)) * sensitivity * (float)(CAMERA_SPEED * dt);
    vertMovement  = (800 / 2.0f - static_cast<float>(py)) * sensitivity * (float)(CAMERA_SPEED * dt);

    // up and down
    rotation.SetToRotation(horizMovement, 0, 1, 0);
    target = (rotation * (target - position)) + position;
    up = rotation * up;

    // left and right
    Vector3 view = (target - position).Normalized();
    Vector3 right = view.Cross(up);
    right.y = 0;
    right.Normalize();
    up = right.Cross(view).Normalized();

    rotation.SetToRotation(vertMovement, right.x, right.y, right.z);
    target = (rotation * (target - position)) + position;

    // set back to middle of the screen
    glfwSetCursorPos(glfwGetCurrentContext(), 1000 / 2.0f, 800 / 2.0f);
}

/******************************************************************************/
/*!
\brief	Helper FPScamera Update function, For viewing up down left right (Keyboard)

\param	dt
    deltatime value
*/
/******************************************************************************/
void FPSCamera::UpdateLooking_KeyB(double dt)
{
    float CAMERA_SPEED = 400.f;
    Mtx44 rotation;
    rotation.SetToIdentity();

    if(Application::IsKeyPressed(VK_LEFT))
	{
        float yaw = (float)(CAMERA_SPEED * dt);
        rotation.SetToRotation(yaw, 0, 1, 0);
        target = (rotation * (target - position)) + position;
		up = rotation * up;
        
	}

	if(Application::IsKeyPressed(VK_RIGHT))
	{
		float yaw = (float)(-CAMERA_SPEED * dt);
		
		rotation.SetToRotation(yaw, 0, 1, 0);
		target = (rotation * (target - position)) + position;
		up = rotation * up;
	}

	if(Application::IsKeyPressed(VK_UP) && theta >= -89.9f)
	{   
		float pitch = (float)(CAMERA_SPEED * dt);
		Vector3 view = (target - position).Normalized();
        Vector3 right = view.Cross(up);
	    right.y = 0;
        right.Normalize();
		up = right.Cross(view).Normalized();
		
		rotation.SetToRotation(pitch, right.x, right.y, right.z);
		target = (rotation * (target - position)) + position;
	}

	if(Application::IsKeyPressed(VK_DOWN) && theta <= 89.9f)
	{
		float pitch = (float)(-CAMERA_SPEED * dt);
		Vector3 view = (target - position).Normalized();        
		Vector3 right = view.Cross(up);                
		right.y = 0;
		right.Normalize();
		up = right.Cross(view).Normalized();
		
		rotation.SetToRotation(pitch, right.x, right.y, right.z);
		target = (rotation * (target - position)) + position;
	}
    
    

    if(Application::IsKeyPressed('Z'))
	{
        Vector3 view = (target - position).Normalized();
		position -= view * (float)(100.f * dt);
	}

    if(Application::IsKeyPressed('X'))
	{
		Vector3 direction = target - position;
		if(direction.Length() > 5)
		{
			Vector3 view = (target - position).Normalized();
			position += view * (float)(100.f * dt);
		}
	}
    
    /*
    if(Application::IsKeyPressed('Z'))
	{
        Vector3 direction = target - position;
		if(direction.Length() > 5)
		{
			Vector3 view = (target - position).Normalized();
			position += view * (float)(100.f * dt);
		}
	}

    if(Application::IsKeyPressed('X'))
	{
        Vector3 view = (target - position).Normalized();
		position -= view * (float)(100.f * dt);
	}
    */


    if(Application::IsKeyPressed(VK_LEFT))
	{
        
	}

	if(Application::IsKeyPressed('R'))
	{
		Reset();
	}
    /*
    const float WALKING_SPEED = 365.0f; //365 cm/s = 3.65 m/s
    const float SPRINTING_SPEED = 520.0f; //520 cm/s = 5.2 m/s

    if(Application::IsKeyPressed('W'))
	{
        position.x += WALKING_SPEED * dt;
        target.x += WALKING_SPEED * dt;
	}

    if(Application::IsKeyPressed('S'))
	{
        position.x += SPRINTING_SPEED * dt;
        target.x += SPRINTING_SPEED * dt;
	}*/
}

/******************************************************************************/
/*!
\brief	To check whether is it facing north or opposite of north direction

\param	a
    camera north value
*/
/******************************************************************************/
int FPSCamera::NORTH(float a)
{
    if (a <= -45.f && a >= -90.f)
    {
        return 0;
    }

    else if (a >= 45.f && a <= 90.f)
    {
        return 1;
    }

    else
    {
        return 2;
    }
}

/******************************************************************************/
/*!
\brief	To check whether is it facing east or opposite of east direction

\param	a
    camera east value
*/
/******************************************************************************/
int FPSCamera::EAST(float a)
{
    if (a <= -45.f && a >= -90.f)
    {
        return 0;
    }

    else if (a >= 45.f && a <= 90.f)
    {
        return 1;
    }

    else
    {
        return 2;
    }
}

/******************************************************************************/
/*!
\brief	reset position
*/
/******************************************************************************/
void FPSCamera::Reset()
{
	position = defaultPosition;
	target = defaultTarget;
	up = defaultUp;
}