/******************************************************************************/
/*!
\file	Utility.h
\author Chuk Yih Jou
\brief  overload the * operator to multiply a matrix with a position
*/
/******************************************************************************/
#ifndef UTILITY_H
#define UTILITY_H

#include "Vertex.h"
#include "Mtx44.h"

Position operator*(const Mtx44& lhs, Position rhs);

#endif