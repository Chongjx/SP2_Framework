/******************************************************************************/
/*!
\file	Collision_detection.cpp
\author Chuk Yih Jou
\brief
check for collision between owner and all hitboxes
*/
/******************************************************************************/
#include "Collision_detection.h"

CCollision_detect::CCollision_detect(void)
{

}

CCollision_detect::~CCollision_detect(void)
{

}

void CCollision_detect::POINTtoAABB(CHitBox_Database& allHitBox, float x, float y, float z, bool &collide)
{
    if (allHitBox.head != NULL)
    {
        allHitBox.current = allHitBox.head;

        while(allHitBox.current != NULL)
        {
            if(x > allHitBox.current->data.min[0] && x < allHitBox.current->data.max[0] &&
                y > allHitBox.current->data.min[1] && y < allHitBox.current->data.max[1] &&
                z > allHitBox.current->data.min[2] && z < allHitBox.current->data.max[2])
            {
                collide = true;
                break;
            }

            else
            {
                allHitBox.current = allHitBox.current->next;
                collide = false;
            }
        }
    }

    else
    {
        collide = false;
    }
}

void CCollision_detect::AABBtoAABB(CHitBox_Database& allHitBox, CCollision_HitBox& owner, bool & collide)
{
   // std::cout << allHitBox.current->data.max[2] << std::endl;
    if (allHitBox.head != NULL)
    {
        allHitBox.current = allHitBox.head;

        while(allHitBox.current != NULL)
        {
            if (allHitBox.current->data.max[0] > owner.min[0] &&
                allHitBox.current->data.min[0] < owner.max[0] && 
                allHitBox.current->data.max[1] > owner.min[1] &&
                allHitBox.current->data.min[1] < owner.max[1] &&
                allHitBox.current->data.max[2] > owner.min[2] &&
                allHitBox.current->data.min[2] < owner.max[2])
            {
                collide = true;
                break;
            }

            else
            {
                allHitBox.current = allHitBox.current->next;
                collide = false;
            }
        }
    }

    else
    {
        collide = false;
    }
}

void CCollision_detect::returnNormal(CCollision_HitBox & allHitBox, CCollision_HitBox & owner, float &normalx, float &normalz)
{
    if (owner.min[0] > allHitBox.max[0] - 10)
    {
        normalx = 1;
        normalz = 0;
    }

    if(owner.max[0] <  allHitBox.min[0] + 10)
    {
        normalx = -1;
        normalz = 0;
    }

    if (owner.min[2] >  allHitBox.max[2] - 10)
    {
        normalx = 0;
        normalz = 1;
    }

    if(owner.max[2] <  allHitBox.min[2] + 10)
    {
        normalx = 0;
        normalz = -1;
    }
}

/*
float getDistance(Vector3 box1, Vector3 box2)
{
    return (box1 - box2).Length();
}

bool checkFront(TAABB box1, TAABB box2, float dis)
{
    //if (cbox[C_CAMERA].c_vecMin.z < cbox[C_DIRT].c_vecMax.z && cbox[C_CAMERA].c_vecMax.z > cbox[C_DIRT].c_vecMin.z && box1.x > cbox[C_DIRT].c_vecMax.x)
    if (box1.c_vecMin.z < box2.c_vecMax.z && box1.c_vecMax.z > box2.c_vecMin.z && getCenter(box1).x > box2.c_vecMax.x && getDistance(getCenter(box1), getCenter(box2)) < dis)
    {
        return true;
    }

    else
    {
        return false;
    }
}

bool checkRight(TAABB box1, TAABB box2, float dis)
{
    //else if (cbox[C_CAMERA].c_vecMin.x < cbox[C_DIRT].c_vecMax.x && cbox[C_CAMERA].c_vecMax.x > cbox[C_DIRT].c_vecMin.x && box1.z > cbox[C_DIRT].c_vecMax.z)
    if (box1.c_vecMin.x < box2.c_vecMax.x && box1.c_vecMax.x > box2.c_vecMin.x && getCenter(box1).z > box2.c_vecMax.z && getDistance(getCenter(box1), getCenter(box2)) < dis)
    {
        return true;
    }

    else
    {
        return false;
    }
}

bool checkBack(TAABB box1, TAABB box2, float dis)
{
    //else if (cbox[C_CAMERA].c_vecMin.z < cbox[C_DIRT].c_vecMax.z && cbox[C_CAMERA].c_vecMax.z > cbox[C_DIRT].c_vecMin.z && box1.x < cbox[C_DIRT].c_vecMin.x)
    if (box1.c_vecMin.z < box2.c_vecMax.z && box1.c_vecMax.z > box2.c_vecMin.z && getCenter(box1).x < box2.c_vecMin.x && getDistance(getCenter(box1), getCenter(box2)) < dis)
    {
        return true;
    }

    else
    {
        return false;
    }
}

bool checkLeft(TAABB box1, TAABB box2, float dis)
{
    //else if (cbox[C_CAMERA].c_vecMin.x < cbox[C_DIRT].c_vecMax.x && cbox[C_CAMERA].c_vecMax.x > cbox[C_DIRT].c_vecMin.x && box1.z < cbox[C_DIRT].c_vecMin.z)
    if (box1.c_vecMin.x < box2.c_vecMax.x && box1.c_vecMax.x > box2.c_vecMin.x && getCenter(box1).z < box2.c_vecMin.z && getDistance(getCenter(box1), getCenter(box2)) < dis)
    {
        return true;
    }

    else
    {
        return false;
    }
}*/