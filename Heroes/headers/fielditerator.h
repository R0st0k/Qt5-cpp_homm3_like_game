#ifndef FIELDITERATOR_H
#define FIELDITERATOR_H
#include "field.h"

class FieldIterator
{
    Field* ptrField;


public:
    FieldIterator();
    void startRead();
    void nextRead();
    void startDraw();
    void nextDraw();
    Cell& current();
    Cell& current(int i, int j);
    bool isDoneRead();
    bool isDoneDraw();
    int getSize();
    QPoint getCell();

    int indexW;
    int indexH;
};

#endif // FIELDITERATOR_H
