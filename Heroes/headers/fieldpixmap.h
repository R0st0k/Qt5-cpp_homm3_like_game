#ifndef FIELDPIXMAP_H
#define FIELDPIXMAP_H
#include <QWidget>
#include <QPainter>
#include <QPaintEvent>

#define CELL_SIZE 32


class Fieldpixmap :public QWidget
{
    Q_OBJECT
public:

    Fieldpixmap(QWidget *parent = 0);

    void keyPressChange(int, int);
    void paintEvent(QPaintEvent*);

    int startXH; //32
    int startYH; //33
    int size;
    QPoint mouseMove;
    QPoint mousePress;
    QPixmap map;
    QPixmap path;
    QPixmap frame;
private:
    void mouseMoveEvent(QMouseEvent*);
    void mousePressEvent(QMouseEvent*);
public slots:
    void slotDrawFullMap(int, int);
signals:
    void signalFullMapChange(QPixmap&, int, int);
    void signalNeedFullMap();
    void signalNeedPath(QPoint);
};

#endif // FIELDPIXMAP_H
