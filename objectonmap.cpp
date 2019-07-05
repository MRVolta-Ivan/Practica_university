#include "objectonmap.h"

ObjectOnMap::ObjectOnMap(int x, int y)
{
    IndexX = x;
    IndexY = y;
}

int ObjectOnMap::GetX()
{
    return IndexX;
}

int ObjectOnMap::GetY()
{
    return IndexY;
}

void ObjectOnMap::SetX(int x)
{
    IndexX = x;
}

void ObjectOnMap::SetY(int y)
{
    IndexY = y;
}
