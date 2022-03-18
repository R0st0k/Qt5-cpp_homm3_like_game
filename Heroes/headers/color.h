#ifndef COLOR_H
#define COLOR_H
#include "heroes.h"

class Color
{
public:
    int resources[6];
    long int gold;
    Hero* heroes;
    int player;
    int color;
};

#endif // COLOR_H
