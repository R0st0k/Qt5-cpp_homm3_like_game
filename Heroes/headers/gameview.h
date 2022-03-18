#ifndef GAMEVIEW_H
#define GAMEVIEW_H
#include "gamecontroller.h"
#include "fieldpixmap.h"
#include "minimap.h"
#include "statusbar.h"
#include "resourcebar.h"

class GameView : public QObject
{
    Q_OBJECT;
public:
    GameView();
    ~GameView();
    GameController * gameController;

    void keyPressChange(int, int);

    Fieldpixmap* gameField;
    MiniMap* miniMap;
    StatusBar* statusBar;
    QLabel* buttons;
    QLabel* infoDesk;
    QLabel* dateBar;
    ResourceBar* resBar;

public slots:
    void slotGameTimer();
    void slotNeedFullMap();
    void slotNeedPath(QPoint);
    void slotFieldChange(int, int);
    void slotGoldChange(int);
    void slotSetFieldSize(int);
    void slotSetStartCam(int, int);
    QPoint slotGetStartCam();
};

#endif // GAMEVIEW_H
