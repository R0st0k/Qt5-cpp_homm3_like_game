#ifndef HERO_H
#define HERO_H
#include <QStack>
#include <QPoint>

class Hero
{
public:
    int attack;
    int defense;
    int spellPower;
    int knowledge;
    int mana;
    int exp;
    int armyPower;
    int move;
    int morality;
    int luck;
    int visibility;
    int color;
    int height;
    int width;
    QStack<QPoint> path;
    ~Hero(){
    }
};

#endif // HERO_H
