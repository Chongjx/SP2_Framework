/******************************************************************************/
/*!
\file	Camera.h
\author Chuk Yih Jou
\brief
To store camera position, target and up
*/
/******************************************************************************/
#ifndef CAMERA_H
#define CAMERA_H

#include "Vector3.h"

/******************************************************************************/
/*!
		Class Camera:
\brief	To store camera position, target and up
*/
/******************************************************************************/

class Camera
{
public:
	Vector3 position;
	Vector3 target;
	Vector3 up;

	Camera();
	~Camera();
	virtual void Init(const Vector3& pos, const Vector3& target, const Vector3& up);
	virtual void Reset();
	virtual void Update(double dt);
};

#endif