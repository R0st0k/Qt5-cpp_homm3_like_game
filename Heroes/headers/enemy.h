#ifndef ENEMY_H
#define ENEMY_H
#include "abstractfactory.h"

enum State{STAY, GO, PATROUL};


class Enemy{
    int direction1 =4;
    int direction2 =4;
    int direction3 =4;
    QPoint aim_;
public:
    int curr_x1;
    int curr_y1;
    int curr_x2;
    int curr_y2;
    int curr_x3;
    int curr_y3;
    State move_condition1=STAY;
    State move_condition2=STAY;
    State move_condition3=STAY;
    Enemy(int x1, int y1, int x2, int y2, int x3, int y3){
        curr_x1 = x1;
        curr_y1 = y1;
        curr_x2 = x2;
        curr_y2 = y2;
        curr_x3 = x3;
        curr_y3 = y3;
    }

    void ChangeCondition(State new_cond, int temp){
        switch (temp) {
        case 1:
            this->move_condition1=new_cond;
        case 2:
            this->move_condition2=new_cond;
        case 3:
            this->move_condition3=new_cond;
        }
    }

    QPoint Get_Aim(){
        return this->aim_;
    }

    void Set_Aim(QPoint aim){
        this->aim_=aim;
        ChangeCondition(GO, 1);
        ChangeCondition(GO, 2);
        ChangeCondition(GO, 3);
    }

    void Move(Field* map, QPoint hero){
        Moving(move_condition1, curr_x1, curr_y1, map, hero, direction1);
        if(abs(curr_x1 - aim_.x()) <= 3 && abs(curr_y1 - aim_.y()) <= 3)
            ChangeCondition(PATROUL, 1);
        Moving(move_condition2, curr_x2, curr_y2, map, hero, direction2);
        if(abs(curr_x2 - aim_.x()) <= 3 && abs(curr_y2 - aim_.y()) <= 3)
            ChangeCondition(PATROUL, 2);
        Moving(move_condition3, curr_x3, curr_y3, map, hero, direction3);
        if(abs(curr_x3 - aim_.x()) <= 3 && abs(curr_y3 - aim_.y()) <= 3)
            ChangeCondition(PATROUL, 3);
    }

    void Moving(State move_condition, int& curr_x, int& curr_y, Field* map, QPoint hero, int& direction){
        if(move_condition==PATROUL){
            if(map->getCell(curr_x, curr_y-1).passability == 0 && QPoint(curr_x, curr_y-1) != hero && QPoint(curr_x, curr_y-1) != QPoint(curr_x1, curr_y1) &&
                QPoint(curr_x, curr_y-1) != QPoint(curr_x2, curr_y2) && QPoint(curr_x, curr_y-1) != QPoint(curr_x3, curr_y3) && abs(curr_y -1 - aim_.y()) <= 3){
                if(direction == 1)
                    curr_y--;
                else
                    direction = 1;
            }
            else if(map->getCell(curr_x-1, curr_y).passability == 0 && QPoint(curr_x-1, curr_y) != hero && QPoint(curr_x-1, curr_y) != QPoint(curr_x1, curr_y1) &&
                     QPoint(curr_x-1, curr_y) != QPoint(curr_x2, curr_y2) && QPoint(curr_x-1, curr_y) != QPoint(curr_x3, curr_y3) && abs(curr_x -1 - aim_.x()) <= 3){
                if(direction == 2)
                    curr_x--;
                else
                    direction = 2;
            }
            else if(map->getCell(curr_x, curr_y+1).passability == 0 && QPoint(curr_x, curr_y+1) != hero && QPoint(curr_x, curr_y+1) != QPoint(curr_x1, curr_y1) &&
                     QPoint(curr_x, curr_y+1) != QPoint(curr_x2, curr_y2) && QPoint(curr_x, curr_y+1) != QPoint(curr_x3, curr_y3) && abs(curr_y +1 - aim_.y()) <= 3){
                if(direction == 3)
                    curr_y++;
                else
                    direction = 3;
            }
            else if(map->getCell(curr_x+1, curr_y).passability == 0 && QPoint(curr_x+1, curr_y) != hero && QPoint(curr_x+1, curr_y) != QPoint(curr_x1, curr_y1) &&
                     QPoint(curr_x+1, curr_y) != QPoint(curr_x2, curr_y2) && QPoint(curr_x+1, curr_y) != QPoint(curr_x3, curr_y3) && abs(curr_x +1 - aim_.x()) <= 3){
                if(direction == 4)
                    curr_x++;
                else
                    direction = 4;
            }
        }
        if(move_condition==GO){
            if(curr_x == aim_.x()){
                if(curr_y < aim_.y()){
                    if(map->getCell(curr_x, curr_y+1).passability == 0 && QPoint(curr_x, curr_y+1) != hero && QPoint(curr_x, curr_y+1) != QPoint(curr_x1, curr_y1) &&
                        QPoint(curr_x, curr_y+1) != QPoint(curr_x2, curr_y2) && QPoint(curr_x, curr_y+1) != QPoint(curr_x3, curr_y3)){
                        curr_y++;
                        return;
                    }

                }
                else if(map->getCell(curr_x, curr_y-1).passability == 0 && QPoint(curr_x, curr_y-1) != hero && QPoint(curr_x, curr_y-1) != QPoint(curr_x1, curr_y1) &&
                         QPoint(curr_x, curr_y-1) != QPoint(curr_x2, curr_y2) && QPoint(curr_x, curr_y-1) != QPoint(curr_x3, curr_y3)){
                    curr_y--;
                    return;
                }
            }
            else if(curr_x < aim_.x()){
                if(map->getCell(curr_x+1, curr_y).passability == 0 && QPoint(curr_x+1, curr_y) != hero && QPoint(curr_x+1, curr_y) != QPoint(curr_x1, curr_y1) &&
                    QPoint(curr_x+1, curr_y) != QPoint(curr_x2, curr_y2) && QPoint(curr_x+1, curr_y) != QPoint(curr_x3, curr_y3)){
                    curr_x++;
                    return;
                }
            }
            else if(map->getCell(curr_x-1, curr_y).passability == 0 && QPoint(curr_x-1, curr_y) != hero && QPoint(curr_x-1, curr_y) != QPoint(curr_x1, curr_y1) &&
                     QPoint(curr_x-1, curr_y) != QPoint(curr_x2, curr_y2) && QPoint(curr_x-1, curr_y) != QPoint(curr_x3, curr_y3)){
                curr_x--;
                return;
            }
            if(map->getCell(curr_x, curr_y-1).passability == 0 && QPoint(curr_x, curr_y-1) != hero && QPoint(curr_x, curr_y-1) != QPoint(curr_x1, curr_y1) &&
                QPoint(curr_x, curr_y-1) != QPoint(curr_x2, curr_y2) && QPoint(curr_x, curr_y-1) != QPoint(curr_x3, curr_y3)){
                curr_y--;
                return;
            }
            else if(map->getCell(curr_x-1, curr_y).passability == 0 && QPoint(curr_x-1, curr_y) != hero && QPoint(curr_x-1, curr_y) != QPoint(curr_x1, curr_y1) &&
                     QPoint(curr_x-1, curr_y) != QPoint(curr_x2, curr_y2) && QPoint(curr_x-1, curr_y) != QPoint(curr_x3, curr_y3)){
                curr_x--;
                return;
            }
            else if(map->getCell(curr_x, curr_y+1).passability == 0 && QPoint(curr_x, curr_y+1) != hero && QPoint(curr_x, curr_y+1) != QPoint(curr_x1, curr_y1) &&
                     QPoint(curr_x, curr_y+1) != QPoint(curr_x2, curr_y2) && QPoint(curr_x, curr_y+1) != QPoint(curr_x3, curr_y3)){
                curr_y++;
                return;
            }
            else if(map->getCell(curr_x+1, curr_y).passability == 0 && QPoint(curr_x+1, curr_y) != hero && QPoint(curr_x+1, curr_y) != QPoint(curr_x1, curr_y1) &&
                     QPoint(curr_x+1, curr_y) != QPoint(curr_x2, curr_y2) && QPoint(curr_x+1, curr_y) != QPoint(curr_x3, curr_y3)){
                curr_x++;
                return;
            }
        }
    }
    void operator+=(Hero* const& hero){
        QSound::play(":/technical/sounds/technical/MILITARY.wav");
    }
};

#endif // ENEMY_H
