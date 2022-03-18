#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
//#include <QtMultimedia/QSound>
#include <QGridLayout>
#include "keycommand.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    Ui::MainWindow *ui;
    GameView* currGame;
    void newGame();
    void keyPressEvent(QKeyEvent*);
    void mousePressEvent(QMouseEvent*);
    QSound* button;
    QGridLayout *leftLayout;
    QGridLayout *rightLayout;
    bool isEnd = false;
    QLabel* temp;
private slots:
    void slotEndGame();
    void on_action_triggered();
    void slotUncorrectData();
    void on_action_3_triggered();
    void on_action_2_triggered();
    void slotSaveProcess();
    void slotEndSave();
};
#endif // MAINWINDOW_H
