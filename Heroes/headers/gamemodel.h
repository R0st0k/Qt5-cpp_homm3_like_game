#ifndef GAMEMODEL_H
#define GAMEMODEL_H
#include <QQueue>
#include <QTimer>
#include <QPainter>
#include "enemy.h"
#include "colorlogger.h"
#include "snapshot.h"

#define CELL_SIZE 32

class GameModel : public QObject, public LogPublisher
{
    Q_OBJECT;
public:
    GameModel();
    ~GameModel();

    void ReadField(QString);
    void DrawField();
    void keyPressChange(int, int);
    QPixmap fullMapDraw();
    Cell getCurrentCell(int, int);
    int** pathFinder(QPoint);
    QPixmap pathDrawer(QPoint, int**);
    void Save(QString);

    QTimer* gameTimer;
private:
    void loadImage();
    QPixmap pathArrowDrawer(QPoint, QPoint, QPoint, bool);
    QString writeLog() const override;

    Command* command;
    QString logString;
    ColorLogger * log;
    Field* originalField;
    Color* colors;
    Heroes* heroes;
    Enemy* enemies;
    QPixmap ** frameSpace;
    QPixmap ** terrain;
    int size;
    int isEnd;

signals:
    void signalSetStartCam(int, int);
    QPoint signalGetStartCam();
    void signalEnd();
    void signalFieldChange(int, int);
    void signalGoldChange(int);
    void signalSetFieldSize(int);
    void signalUncorrectData();
    void signalSaveProcess();
    void signalEndSave();
};

#endif // GAMEMODEL_H
