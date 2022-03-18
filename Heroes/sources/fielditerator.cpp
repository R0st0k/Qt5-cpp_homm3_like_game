#include "../headers/fielditerator.h"

FieldIterator::FieldIterator() {
    ptrField = &Field::getField();
    indexH = 9;
    indexW = 9;
}

void FieldIterator::startRead() {
    indexH = 9;
    indexW = 9;
}

void FieldIterator::startDraw() {
    indexH = 0;
    indexW = 0;
}

void FieldIterator::nextRead() {
    if ((indexW + 1) == ptrField->size-9) {
        indexH++;
        indexW = 9;
    }
    else
        indexW++;
}

void FieldIterator::nextDraw() {
    if ((indexW + 1) == ptrField->size) {
        indexH++;
        indexW = 0;
    }
    else
        indexW++;
}

Cell& FieldIterator::current() {
    return ptrField->getCell(indexH, indexW);
}

Cell& FieldIterator::current(int i, int j){
    return ptrField->getCell(i, j);
}

bool FieldIterator::isDoneRead() {
    return indexH == ptrField->size-9;
}

bool FieldIterator::isDoneDraw() {
    return indexH == ptrField->size;
}

int FieldIterator::getSize(){
    return ptrField->size;
}

QPoint FieldIterator::getCell(){
    return QPoint(indexH, indexW);
}
