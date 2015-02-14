#include "Collision_Node.h"

int CCollision_Node::count = 0;

CCollision_Node::CCollision_Node(void)
{
    next = NULL;
    back = NULL;
    count++;
}

CCollision_Node::CCollision_Node(CCollision_HitBox newData)
{
    data = newData;
    next = NULL;
    back = NULL;
    count++;
}

CCollision_Node::~CCollision_Node(void)
{
    count--;
}

void CCollision_Node::setCount(int c)
{
    count = c;
}

int CCollision_Node::getCount(void)
{
    return count;
}