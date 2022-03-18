#ifndef MINIMAP_H
#define MINIMAP_H
#include <QWidget>
#include <QPainter>
#include <QPaintEvent>

#define CELL_SIZE 32

class MiniMap :public QWidget
{
    Q_OBJECT
public:
    MiniMap();

    void paintEvent(QPaintEvent*);
    void mouseMoveEvent(QMouseEvent*);
    void mousePressEvent(QMouseEvent*);

    QPixmap radar;
    QPixmap frame;
    QPixmap smallMap;

public slots:
    void slotDrawMiniMap(QPixmap&, int, int);

signals:
    void signalMiniMapChange(int, int);
};

#endif // MINIMAP_H
