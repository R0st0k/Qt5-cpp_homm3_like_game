#ifndef FIELD_H
#define FIELD_H
#include "cell.h"

#define SMALL_SIZE_FIELD 36
#define MEDIUM_SIZE_FIELD 72
#define LARGE_SIZE_FIELD 108
#define XLARGE_SIZE_FIELD 144
#define HUGE_SIZE_FIELD 180
#define XHUGE_SIZE_FIELD 216
#define GIANT_SIZE_FIELD 252

class Field
{
private:
    Field();
    Field(Field const&);
    Field& operator=(Field const&);

    Cell** fieldGrid;

public:
    ~Field();
    int size;
    Field(Field&&);
    Field& operator=(Field&&);
    static Field& getField();
    Cell& getCell(int width, int height);
};

#endif // FIELD_H
