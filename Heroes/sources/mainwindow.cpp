#include "../headers/mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QFileDialog>
#include <QString>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QString path = QFileDialog::getOpenFileName(this, "Открыть файл", "", "*.txt");
    if(path.isEmpty())
        path = ":/maps/maps/small_map.txt";
    currGame = new GameView;
    connect(currGame->gameController->gameModel, &GameModel::signalSetFieldSize, currGame, &GameView::slotSetFieldSize);
    connect(currGame->gameController->gameModel->gameTimer, &QTimer::timeout, currGame, &GameView::slotGameTimer);
    connect(currGame->gameField, &Fieldpixmap::signalFullMapChange, currGame->miniMap, &MiniMap::slotDrawMiniMap);
    connect(currGame->miniMap, &MiniMap::signalMiniMapChange, currGame->gameField, &Fieldpixmap::slotDrawFullMap);
    connect(currGame->gameField, &Fieldpixmap::signalNeedFullMap, currGame, &GameView::slotNeedFullMap);
    connect(currGame->gameField, &Fieldpixmap::signalNeedPath, currGame, &GameView::slotNeedPath);
    connect(currGame->gameController->gameModel, &GameModel::signalFieldChange, currGame, &GameView::slotFieldChange);
    connect(currGame->gameController->gameModel, &GameModel::signalGoldChange, currGame, &GameView::slotGoldChange);
    connect(currGame->gameController->gameModel, &GameModel::signalEnd, this, &MainWindow::slotEndGame);
    connect(currGame->gameController->gameModel, &GameModel::signalSetStartCam, currGame, &GameView::slotSetStartCam);
    connect(currGame->gameController->gameModel, &GameModel::signalGetStartCam, currGame, &GameView::slotGetStartCam);
    connect(currGame->gameController->gameModel, &GameModel::signalUncorrectData, this, &MainWindow::slotUncorrectData);
    connect(currGame->gameController->gameModel, &GameModel::signalSaveProcess, this, &MainWindow::slotSaveProcess);
    connect(currGame->gameController->gameModel, &GameModel::signalEndSave, this, &MainWindow::slotEndSave);

    leftLayout = new QGridLayout;
    leftLayout->setSpacing(0);
    ui->mainLayout->addLayout(leftLayout, 0, 0);
    rightLayout = new QGridLayout;
    rightLayout->setSpacing(0);
    ui->mainLayout->addLayout(rightLayout, 0, 1);

    currGame->gameController->gameModel->ReadField(path);


    /*QPushButton* turn = new QPushButton(this);
    turn->setStyleSheet("background-image: url(:/technical/images/technical/iam001n.bmp);");
    turn->move(500, 300);
    turn->setMinimumSize(64, 32);
    turn->setMaximumSize(64, 32);*/

    leftLayout->addWidget(currGame->gameField, 0, 0);
    rightLayout->addWidget(currGame->miniMap, 0, 0);
    leftLayout->addWidget(currGame->statusBar, 1, 0);
    rightLayout->addWidget(currGame->buttons, 1, 0);
    rightLayout->addWidget(currGame->infoDesk, 2, 0);
    rightLayout->addWidget(currGame->dateBar, 3, 0);
    leftLayout->addWidget(currGame->resBar->tree, 2, 0);
    leftLayout->addWidget(currGame->resBar->mercury, 2, 0);
    leftLayout->addWidget(currGame->resBar->ore, 2, 0);
    leftLayout->addWidget(currGame->resBar->sulfur, 2, 0);
    leftLayout->addWidget(currGame->resBar->crystal, 2, 0);
    leftLayout->addWidget(currGame->resBar->gem, 2, 0);
    leftLayout->addWidget(currGame->resBar->gold, 2, 0);
    if(isEnd)
        slotEndGame();
//    rightLayout->addWidget(turn, 1, 0);

    QCursor screenCursor = QCursor(QPixmap(":/technical/images/technical/CursrA00.png"));
    this->setCursor(screenCursor);

    button = new QSound(":/technical/sounds/technical/BUTTON.WAV");

    //QSound *qwer = new QSound(":/technical/sounds/technical/BUILDTWN.WAV");
    //qwer->setLoops(QSound::Infinite);
    //qwer->play();
}

MainWindow::~MainWindow()
{
//    QApplication::quit();
    delete ui;
    delete currGame;
    delete button;
}

void MainWindow::keyPressEvent(QKeyEvent* event){
    if(event->key() == Qt::Key_Up){
        KeyCommand * Up = new UpKeyCommand;
        Up->Execute(currGame);
        delete Up;
    }
    if(event->key() == Qt::Key_Down){
        KeyCommand * Down = new DownKeyCommand;
        Down->Execute(currGame);
        delete Down;
    }
    if(event->key() == Qt::Key_Right){
        KeyCommand * Right = new RightKeyCommand;
        Right->Execute(currGame);
        delete Right;
    }
    if(event->key() == Qt::Key_Left){
        KeyCommand * Left = new LeftKeyCommand;
        Left->Execute(currGame);
        delete Left;
    }
    if(event->key() == Qt::Key_F4){
        newGame();
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event){
    button->play();
    Q_UNUSED(event);
}

void MainWindow::newGame(){
    delete currGame;
    currGame = new GameView;
    QString path = QFileDialog::getOpenFileName(this, "Открыть файл", "", "*.txt");
    if(path.isEmpty())
        path = ":/maps/maps/small_map.txt";
    connect(currGame->gameController->gameModel, &GameModel::signalSetFieldSize, currGame, &GameView::slotSetFieldSize);
    connect(currGame->gameController->gameModel->gameTimer, &QTimer::timeout, currGame, &GameView::slotGameTimer);
    connect(currGame->gameField, &Fieldpixmap::signalFullMapChange, currGame->miniMap, &MiniMap::slotDrawMiniMap);
    connect(currGame->miniMap, &MiniMap::signalMiniMapChange, currGame->gameField, &Fieldpixmap::slotDrawFullMap);
    connect(currGame->gameField, &Fieldpixmap::signalNeedFullMap, currGame, &GameView::slotNeedFullMap);
    connect(currGame->gameField, &Fieldpixmap::signalNeedPath, currGame, &GameView::slotNeedPath);
    connect(currGame->gameController->gameModel, &GameModel::signalFieldChange, currGame, &GameView::slotFieldChange);
    connect(currGame->gameController->gameModel, &GameModel::signalGoldChange, currGame, &GameView::slotGoldChange);
    connect(currGame->gameController->gameModel, &GameModel::signalEnd, this, &MainWindow::slotEndGame);
    connect(currGame->gameController->gameModel, &GameModel::signalSetStartCam, currGame, &GameView::slotSetStartCam);
    connect(currGame->gameController->gameModel, &GameModel::signalGetStartCam, currGame, &GameView::slotGetStartCam);
    connect(currGame->gameController->gameModel, &GameModel::signalUncorrectData, this, &MainWindow::slotUncorrectData);
    connect(currGame->gameController->gameModel, &GameModel::signalSaveProcess, this, &MainWindow::slotSaveProcess);
    connect(currGame->gameController->gameModel, &GameModel::signalEndSave, this, &MainWindow::slotEndSave);
    currGame->gameController->gameModel->ReadField(path);
    leftLayout->addWidget(currGame->gameField, 0, 0);
    rightLayout->addWidget(currGame->miniMap, 0, 0);
    leftLayout->addWidget(currGame->statusBar, 1, 0);
    rightLayout->addWidget(currGame->buttons, 1, 0);
    rightLayout->addWidget(currGame->infoDesk, 2, 0);
    rightLayout->addWidget(currGame->dateBar, 3, 0);
    leftLayout->addWidget(currGame->resBar->tree, 2, 0);
    leftLayout->addWidget(currGame->resBar->mercury, 2, 0);
    leftLayout->addWidget(currGame->resBar->ore, 2, 0);
    leftLayout->addWidget(currGame->resBar->sulfur, 2, 0);
    leftLayout->addWidget(currGame->resBar->crystal, 2, 0);
    leftLayout->addWidget(currGame->resBar->gem, 2, 0);
    leftLayout->addWidget(currGame->resBar->gold, 2, 0);
    if(isEnd)
        slotEndGame();
}

void MainWindow::slotEndGame(){
    QLabel* end = new QLabel;
    end->setMinimumSize(800, 600);
    end->setAlignment(Qt::AlignCenter);
    end->setStyleSheet("font: 30px Times New Roman;"
                           "color: white;");
    end->setText("Конец Игры");
    leftLayout->addWidget(end, 0, 0);
    isEnd = true;
}

void MainWindow::on_action_triggered()
{
    newGame();
}

void MainWindow::slotUncorrectData(){
    QMessageBox::StandardButton reply = QMessageBox::warning(this, "Ошибка", "Выбран файл с некорректными данными, попробуйте еще раз", QMessageBox::Ok);
    if(reply){
        newGame();
    }
}

void MainWindow::on_action_3_triggered()
{
    QApplication::quit();
}

void MainWindow::on_action_2_triggered()
{
    QString path = QFileDialog::getOpenFileName(this, "Сохранить игру", "", "*.txt");
    if(path.isEmpty())
        return;
    currGame->gameController->gameModel->Save(path);
}

void MainWindow::slotSaveProcess(){
    temp = new QLabel;
    temp->setMinimumSize(800, 600);
    temp->setAlignment(Qt::AlignCenter);
    temp->setStyleSheet("font: 30px Times New Roman;"
                       "color: red;");
    temp->setText("Сохранение, подождите");
    leftLayout->addWidget(temp, 0, 0);
    temp->grabKeyboard();
}

void MainWindow::slotEndSave(){
    delete temp;
}
