#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H
#include "gamemodel.h"

class GameController
{
public:
    GameController();
    ~GameController();
    GameModel* gameModel;
    QPixmap fullMapDrawTask();
    Cell getCurrentCellTask(int, int);
    QPixmap pathDrawTask(QPoint);
    void playerMoveTask(int, int);
};

#endif // GAMECONTROLLER_H
