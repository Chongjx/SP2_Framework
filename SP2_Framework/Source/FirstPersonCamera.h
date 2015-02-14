/******************************************************************************/
/*!
\file	FirstPersonCamera.h
\author Team NoticeMeSenpai
\brief
FPS camera system
*/
/******************************************************************************/
#ifndef CAMERA_3_H
#define CAMERA_3_H

#include "Camera.h"
#include "MatrixStack.h"

/******************************************************************************/
/*!
		Class Camera3:
\brief	First Person Camera System
*/
/******************************************************************************/

class FPSCamera : public Camera
{

public:
	Vector3 defaultPosition;
	Vector3 defaultTarget;
	Vector3 defaultUp;

	FPSCamera();
	~FPSCamera();

	void Init(const Vector3& pos, const Vector3& target, const Vector3& up);

	void Update(double dt);
    void UpdateMovement(double dt);
    void UpdateLooking_Mouse(double dt);
    void UpdateLooking_KeyB(double dt);

	void Reset();

    int NORTH(float a);
    int EAST(float a);

    MS rotationStack;

    double px, py;
    float sensitivity;
    float horizMovement;
    float vertMovement; 

    float north;
    float east;

    float yaw;
    float pitch;

    float p;
    float theta;
    float phi;
};

#endif