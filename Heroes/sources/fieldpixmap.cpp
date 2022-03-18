#include "../headers/fieldpixmap.h"

Fieldpixmap::Fieldpixmap(QWidget *parent): QWidget(parent)
{
    this->setObjectName("field");
    this->setMouseTracking(true);
    this->setMinimumSize(608, 555);
    mouseMove.setX(336);
    mouseMove.setY(304);
    frame = QPixmap(":/technical/images/technical/608_555.png");
    path = QPixmap(CELL_SIZE*size, CELL_SIZE*size);
    path.fill(Qt::transparent);
}

void Fieldpixmap::paintEvent(QPaintEvent *event){
    emit signalNeedFullMap();
    emit signalFullMapChange(map, startXH, startYH);
    QPainter mapPainter(this);
    mapPainter.drawPixmap(0, 7, map.copy(startXH*CELL_SIZE, startYH*CELL_SIZE, 608, 546));
    mapPainter.drawPixmap(0, 7, path.copy(startXH*CELL_SIZE, startYH*CELL_SIZE, 608, 546));
    mapPainter.drawPixmap(0, 0, frame);
    mapPainter.end();
    QWidget::paintEvent(event);

}

void Fieldpixmap::slotDrawFullMap(int x, int y){
    startXH = (int)(x / (144 / (size - 18)));
    if(startXH < 0)
        startXH = 0;
    if(startXH + 19 > size)
        startXH = size - 19;
    startYH = (int)(y / (144 / (size - 18))) + 1;
    if(startYH < 0)
        startYH = 0;
    if(startYH + 18 > size)
        startYH = size - 18;
    update();
}

void Fieldpixmap::mouseMoveEvent(QMouseEvent *event){
    mouseMove.setX(event->x());
    mouseMove.setY(event->y());
}

void Fieldpixmap::mousePressEvent(QMouseEvent *event){
    emit signalNeedPath(QPoint(event->x(), event->y()));
    mousePress.setX(event->x());
    mousePress.setY(event->y());
}

void Fieldpixmap::keyPressChange(int x, int y){
    if(startXH + x >= 0 && startXH + x + 19 <= size && x != 0){
        startXH += x;
        update();
    }
    if(startYH + y >= 0 && startYH + y + 18 <= size && y != 0){
        startYH += y;
        update();
    }
}
