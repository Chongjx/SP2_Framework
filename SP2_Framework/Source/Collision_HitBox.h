/******************************************************************************/
/*!
\file	Collision_HitBox.h
\author Chuk Yih Jou
\brief

*/
/******************************************************************************/
#ifndef COLLISION_HITBOX_H
#define COLLISION_HITBOX_H

#include <string>
using std::string;

class CCollision_HitBox
{
    enum XYZ
    {
        x = 0,
        y,
        z,
        total
    };

public:
    CCollision_HitBox(void);
    CCollision_HitBox(float mx, float my, float mz, float nx, float ny, float nz, std::string name);
    ~CCollision_HitBox(void);
    
    int max[total];
    int min[total];
    string name;
};
#endif