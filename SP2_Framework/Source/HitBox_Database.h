/******************************************************************************/
/*!
\file	HitBox_Database.h
\author Chuk Yih Jou
\brief

*/
/******************************************************************************/
#ifndef HITBOX_DATABASE_H
#define HITBOX_BDATABASE_H

#include "Collision_Node.h"
#define NULL 0

class CHitBox_Database
{
public:
    CHitBox_Database(void);
    ~CHitBox_Database(void);

    void Insert(CCollision_HitBox newData);
    bool Delete(CCollision_HitBox newData);

    CCollision_Node *head, *tail, *current, *newNode, *prev;
};
#endif