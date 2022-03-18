#ifndef ABSTRACTFACTORY_H
#define ABSTRACTFACTORY_H
#include "object.h"
#include "fielditerator.h"

class AbstractFactory
{
public:
    virtual void createStone(FieldIterator) = 0;
    virtual void createBonfire(FieldIterator) = 0;
    virtual void createCastle(FieldIterator, int color) = 0;
    virtual void createStronghold(FieldIterator, int color) = 0;
    virtual void createFortress(FieldIterator, int color) = 0;
};

class GrassFactory : public AbstractFactory
{
public:
    void createStone(FieldIterator iter) override{
        iter.current().passability = 2;
        iter.current().objectItem = new Stone(iter.getCell().x(), iter.getCell().y());
    }
    void createBonfire(FieldIterator iter) override{
        iter.current().passability = 1;
        iter.current().objectItem = new Bonfire(iter.getCell().x(), iter.getCell().y());
    }
    void createCastle(FieldIterator iter, int color) override{
        iter.current().passability = 1;
        iter.current().objectItem = new Castle(color, iter.getCell().x(), iter.getCell().y());
        QPoint point = iter.getCell();
        for(int i = point.x()-2; i <= point.x(); i++){
            for(int j = point.y()-2; j <= point.y()+2; j++){
                if((i == point.x()-2 && (j == point.y()-2 || j == point.y()+2)) || (i == point.x() && j == point.y()))
                    continue;
                iter.current(i, j).passability = 2;
                iter.current(i, j).objectItem = iter.current().objectItem;
            }
        }
    }
    void createStronghold(FieldIterator iter, int color) override{
        iter.current().passability = 1;
        iter.current().objectItem = new Stronghold(color, iter.getCell().x(), iter.getCell().y());
        QPoint point = iter.getCell();
        for(int i = point.x()-2; i <= point.x(); i++){
            for(int j = point.y()-2; j <= point.y()+2; j++){
                if((i == point.x()-2 && (j == point.y()-2 || j == point.y()+2)) || (i == point.x() && j == point.y()))
                    continue;
                iter.current(i, j).passability = 2;
                iter.current(i, j).objectItem = iter.current().objectItem;
            }
        }
    }
    void createFortress(FieldIterator iter, int color) override{
        iter.current().passability = 1;
        iter.current().objectItem = new Fortress(color, iter.getCell().x(), iter.getCell().y());
        QPoint point = iter.getCell();
        for(int i = point.x()-2; i <= point.x(); i++){
            for(int j = point.y()-2; j <= point.y()+2; j++){
                if((i == point.x()-2 && (j == point.y()-2 || j == point.y()+2)) || (i == point.x() && j == point.y()))
                    continue;
                iter.current(i, j).passability = 2;
                iter.current(i, j).objectItem = iter.current().objectItem;
            }
        }
    }
};


#endif // ABSTRACTFACTORY_H
