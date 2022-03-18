#include "../headers/minimap.h"

MiniMap::MiniMap(){
   this->setObjectName("miniMap");
   this->setMinimumSize(192, 193);
   radar.load(":/technical/images/technical/Radar.png");
   frame.load(":/technical/images/technical/MiniMap.png");
   QPixmap temp(144, 144);
   smallMap = temp;
}

void MiniMap::slotDrawMiniMap(QPixmap& map, int x, int y){
    QPixmap smallMapWithFrame = map.scaled(144/((map.size().width()/32)-18)*(map.size().width()/32), 144/((map.size().width()/32)-18)*(map.size().width()/32));
    QPainter qp(&smallMapWithFrame);
    qp.drawPixmap(x*144/((map.size().width()/32)-18), y*144/((map.size().width()/32)-18), radar);
    qp.end();
    QPainter qw(&smallMap);
    qw.drawPixmap(0, 0, smallMapWithFrame.copy(144/((map.size().width()/32)-18)*9, 144/((map.size().width()/32)-18)*9, 144, 144));
    qw.end();
    update();
}

void MiniMap::paintEvent(QPaintEvent *event){
    QPainter qp(this);
    qp.drawPixmap(0, 0, frame);
    qp.drawPixmap(23, 26, smallMap);
    qp.end();
    QWidget::paintEvent(event);
}

void MiniMap::mouseMoveEvent(QMouseEvent *event){
    if(23 <= event->x() && event->x() < 23+144 && 26 <= event->y() && event->y() < 26+144)
        emit signalMiniMapChange(event->x()-23, event->y()-26);
}

void MiniMap::mousePressEvent(QMouseEvent *event){
    if(23 <= event->x() && event->x() < 23+144 && 26 <= event->y() && event->y() < 26+144)
        emit signalMiniMapChange(event->x()-23, event->y()-26);
}
