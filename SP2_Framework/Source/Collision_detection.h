/******************************************************************************/
/*!
\file	Collision_detection.h
\author Chuk Yih Jou
\brief
Class to build ...
*/
/******************************************************************************/

#ifndef COLLISION_DETECTION_H
#define COLLISION_DETECTION_H

#include "HitBox_Database.h"

/******************************************************************************/
/*!
Class Collision_detect:
\brief	Provide methods to build a SceneTexture for assignment 2
*/
/******************************************************************************/
class CCollision_detect
{
public:
    CCollision_detect(void);
    ~CCollision_detect(void);

    void AABBtoAABB(CHitBox_Database & allHitBox, CCollision_HitBox & owner, bool & collide);
    
    void returnNormal(CCollision_HitBox & allHitBox, CCollision_HitBox & owner, float &normalx, float &normalz);
    void POINTtoAABB(CHitBox_Database & allHitBox, float x, float y, float z, bool &collide);

};

#endif