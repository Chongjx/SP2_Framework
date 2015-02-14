/******************************************************************************/
/*!
\file	Light.h
\author Chuk Yih Jou
\brief
Struct to provide all variables for light object
*/
/******************************************************************************/

#ifndef LIGHT_H
#define LIGHT_H

#include "Vertex.h"

/******************************************************************************/
/*!
		Class Light:
\brief	provide Light object variables to set up
*/
/******************************************************************************/

struct Light
{
	enum LIGHT_TYPE
	{
		LIGHT_POINT = 0,
		LIGHT_DIRECTIONAL,
		LIGHT_SPOT,
	};
	
	Position position;
	Color color;
	LIGHT_TYPE type;
	Vector3 spotDirection;
	float power;
	float kC, kL, kQ;
	float cosCutoff;
	float cosInner;
	float exponent;

	Light()
	{
		
	}
};

#endif