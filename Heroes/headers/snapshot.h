#ifndef SNAPSHOT_H
#define SNAPSHOT_H
#include "headers/gamemodel.h"
#include <QTextStream>
#include <QDebug>

class Snapshot{
public:
    Field* originalfield;
    QPoint hero;
    int gold;
    QPoint camera;
    QPoint enemy1;
    QPoint enemy2;
    QPoint enemy3;
    int isEnd;
    Snapshot(Field* originalfield, QPoint hero, QPoint camera, int gold, QPoint enemy1, QPoint enemy2, QPoint enemy3, int isEnd){
        this->originalfield = originalfield;
        this->hero = hero;
        this->camera = camera;
        this->gold = gold;
        this->enemy1 = enemy1;
        this->enemy2 = enemy2;
        this->enemy3 = enemy3;
        this->isEnd = isEnd;
    }
};

class Command{
private:
    Snapshot* currState;
    bool changed = false;
public:
    ~Command(){
        if(changed)
            delete currState;
    }
    void change(Snapshot* newSnap){
        if(changed)
            delete currState;
        changed = true;
        currState = newSnap;
    }
    void saveCommand(QString path){
        QFile map(path);

        if (!map.open(QIODevice::WriteOnly | QIODevice::Text)){
            return;
        }
        QTextStream out(&map);
        FieldIterator iter;
        iter.startRead();
        for(int i = 9; i < iter.getSize()-9; i++){
            for(int j = 9; j < iter.getSize()-9; j++){
                out << '#' << iter.current().terrain << iter.current().terrainPatern << iter.current().terrainRotate << iter.current().object << iter.current().objectPatern1 <<iter.current().objectPatern2;
                if(j != iter.getSize()-10)
                    out << ' ';
                iter.nextRead();
            }
            out << endl;
        }
        out << currState->hero.x() << ' ' << currState->hero.y() << ' ' << currState->camera.x() << ' ' << currState->camera.y() << ' ' << currState->gold << endl;
        out << currState->enemy1.x() << ' ' << currState->enemy1.y() << ' ' << currState->enemy2.x() << ' ' << currState->enemy2.y() << ' ' << currState->enemy3.x() << ' ' << currState->enemy3.y() << endl;
        out << currState->isEnd;
        map.close();
    }
};

#endif // SNAPSHOT_H
