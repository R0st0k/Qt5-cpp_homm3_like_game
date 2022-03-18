
#include "../headers/gameview.h"

GameView::GameView(){
    gameController = new GameController;
    gameField = new Fieldpixmap;
    miniMap = new MiniMap;
    statusBar = new StatusBar;
    resBar = new ResourceBar;
    buttons = new QLabel;
    buttons->setObjectName("buttons");
    buttons->setMinimumSize(192, 196);
    buttons->setStyleSheet("background-image: url(:/technical/images/technical/Buttons.png)");
    infoDesk = new QLabel;
    infoDesk->setObjectName("infoDesk");
    infoDesk->setMinimumSize(192, 186);
    infoDesk->setStyleSheet("background-image: url(:/technical/images/technical/InfoDesk.png)");
    dateBar = new QLabel;
    dateBar->setObjectName("dateBar");
    dateBar->setMinimumSize(192, 25);
    dateBar->setAlignment(Qt::AlignCenter);
    dateBar->setStyleSheet("background-image: url(:/technical/images/technical/DateBar.png);"
                           "font: 12px Times New Roman;"
                           "color: white;");
    dateBar->setText("Месяц: 1, Неделя: 1, День: 1");
}

GameView::~GameView(){
    delete gameField;
    delete miniMap;
    delete statusBar;
    delete buttons;
    delete infoDesk;
    delete dateBar;
    delete resBar;
    delete gameController;
}

void GameView::slotSetStartCam(int startx, int starty){
    gameField->startXH = startx;
    gameField->startYH = starty;
}

QPoint GameView::slotGetStartCam(){
    return QPoint(gameField->startXH, gameField->startYH);
}

void GameView::slotGameTimer(){
    gameField->update();
    int i = gameField->startYH + (int)(gameField->mouseMove.y() / 32);
    int j = gameField->startXH + (int)(gameField->mouseMove.x() / 32);
    Cell cell = gameController->getCurrentCellTask(i, j);
    QCursor screenCursor = QCursor(cell.objectItem->cursor(cell.passability));
    gameField->setCursor(screenCursor);

    if(cell.isFrame){
        statusBar->setText("");
        return;
    }
    if(cell.objectItem){
        statusBar->setText(cell.objectItem->statusBar());
        return;
    }
    statusBar->setText("");
}

void GameView::slotNeedFullMap(){
    gameField->map = gameController->fullMapDrawTask();
}

void GameView::slotNeedPath(QPoint pathEnd){
    if(pathEnd != gameField->mousePress && !gameController->getCurrentCellTask(gameField->startYH + (int)(pathEnd.y() / 32), gameField->startXH + (int)(pathEnd.x() / 32)).isFrame && gameController->getCurrentCellTask(gameField->startYH + (int)(pathEnd.y() / 32), gameField->startXH + (int)(pathEnd.x() / 32)).passability != 2){
        QPoint target = QPoint((gameField->startYH + (int)(pathEnd.y() / 32))-9, (gameField->startXH + (int)(pathEnd.x() / 32))-9);
        gameField->path = gameController->pathDrawTask(target);
    }
}

void GameView::keyPressChange(int x, int y){
    gameController->playerMoveTask(x, y);
}

void GameView::slotFieldChange(int x, int y){
    gameField->startXH = x;
    gameField->startYH = y;
    gameField->update();
}

void GameView::slotGoldChange(int gold){
    resBar->gold->setText(QString::number(gold));
}

void GameView::slotSetFieldSize(int size){
    gameField->size = size;
}
