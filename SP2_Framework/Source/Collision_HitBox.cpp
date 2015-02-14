#include "Collision_HitBox.h"

CCollision_HitBox::CCollision_HitBox(void)
{
    max[x] = 0;
    max[y] = 0;
    max[z] = 0;

    min[x] = 0;
    min[y] = 0;
    min[z] = 0;

    name = "error";
}

CCollision_HitBox::CCollision_HitBox(float mx, float my, float mz, float nx, float ny, float nz, std::string n)
{
    max[x] = mx;
    max[y] = my;
    max[z] = mz;

    min[x] = nx;
    min[y] = ny;
    min[z] = nz;

    name = n;
}

CCollision_HitBox::~CCollision_HitBox(void)
{

}