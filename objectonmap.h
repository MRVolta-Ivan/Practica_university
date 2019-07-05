#ifndef OBJECTONMAP_H
#define OBJECTONMAP_H

class ObjectOnMap
{
protected:
    int IndexX; //Координата по x
    int IndexY; //Координата по y
public:
    ObjectOnMap(int x, int y);
    int GetX();
    int GetY();
    void SetX(int x);
    void SetY(int y);
};

#endif // OBJECTONMAP_H
