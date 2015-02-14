/******************************************************************************/
/*!
\file	Collision_Node.h
\author Chuk Yih Jou
\brief

*/
/******************************************************************************/
#ifndef COLLISION_NODE_H
#define COLLISION_NODE_H

#include "Collision_Hitbox.h"

class CCollision_Node
{
private:
    static int count;

public:
    CCollision_Node(void);
    CCollision_Node(CCollision_HitBox newData);
    ~CCollision_Node(void);

    CCollision_HitBox data; 
    CCollision_Node* next;
    CCollision_Node* back;

    static void setCount(int);
    static int getCount(void);
};
#endif