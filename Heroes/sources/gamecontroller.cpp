#include "./headers/gamecontroller.h"

GameController::GameController(){
    gameModel = new GameModel;
}

GameController::~GameController(){
    delete gameModel;
}

QPixmap GameController::fullMapDrawTask(){
    return gameModel->fullMapDraw();
}

Cell GameController::getCurrentCellTask(int i, int j){
    return gameModel->getCurrentCell(i, j);
}

QPixmap GameController::pathDrawTask(QPoint target){
    return gameModel->pathDrawer(target, gameModel->pathFinder(target));
}

void GameController::playerMoveTask(int x, int y){
    gameModel->keyPressChange(x, y);
}
