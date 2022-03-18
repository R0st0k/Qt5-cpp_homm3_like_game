#ifndef CELL_H
#define CELL_H
#include "object.h"


class Cell
{
public:
    Cell();
    int terrain;
    int terrainPatern;
    int terrainRotate;
    int object;
    int objectPatern1;
    int objectPatern2;
    int passability;
    bool isFrame;
    Object* objectItem;
};

#endif // CELL_H
