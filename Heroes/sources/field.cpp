#include "../headers/field.h"

Field::Field()
{
    size = SMALL_SIZE_FIELD + 18;
    fieldGrid = new Cell * [size];
    for (int i = 0; i < size; i++)
        fieldGrid[i] = new Cell[size];
}

Field::~Field() {
    /*for(int i = 0; i < size; i++)
        for(int j = 0; j < size; j++)
            if(!fieldGrid[i][j].objectItem)
                delete fieldGrid[i][j].objectItem;*/
    for(int i = 0; i < size; i++)
        for(int j = 0; j < size; j++)
            delete fieldGrid[i][j].objectItem;
    for (int i = 0; i < size; i++)
        delete[] fieldGrid[i];
    delete[] fieldGrid;

}

Field::Field(Field const& original){
    size = original.size;
    fieldGrid = new Cell* [size];
    for(int i = 0; i < size; i++){
        fieldGrid[i] = new Cell [size];
        for(int j = 0; j < size; j++)
            fieldGrid[i][j] = original.fieldGrid[i][j];
    }
}

Field& Field::operator=(Field const& original){
    if (this == &original)
        return *this;

    for(int i = 0; i < size; i++)
        delete [] fieldGrid[i];
    delete [] fieldGrid;

    size = original.size;
    fieldGrid = new Cell* [size];
    for(int i = 0; i < size; i++){
        fieldGrid[i] = new Cell [size];
        for(int j = 0; j < size; j++)
            fieldGrid[i][j] = original.fieldGrid[i][j];
    }
    return *this;
}

Field::Field(Field&& original) {
    fieldGrid = original.fieldGrid;
    original.fieldGrid = nullptr;
}

Field& Field::operator=(Field&& original) {
    if (this == &original)
        return *this;

    for (int i = 0; i < size; i++)
        delete[] fieldGrid[i];
    delete[] fieldGrid;

    fieldGrid = original.fieldGrid;
    original.fieldGrid = nullptr;

    return *this;
}

Field& Field::getField() {
    static Field original;
    return original;
}

Cell& Field::getCell(int width, int height) {
    return fieldGrid[height][width];
}
