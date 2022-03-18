#ifndef OBJECT_H
#define OBJECT_H
#include <QString>
#include <QPixmap>
#include <QSound>
#include "logpublisher.h"
#include "color.h"

class Object : public LogPublisher
{
public:
    virtual ~Object() {};
    virtual QString statusBar() = 0;
    QPixmap cursor(int passability){
        if(passability == 2)
            return QPixmap(":/technical/images/technical/CursrA00.png");
        if(passability == 1)
            return QPixmap(":/technical/images/technical/CursrA24.png");
        if(passability == 0)
            return QPixmap(":/technical/images/technical/CursrA20.png");
        return QPixmap(":/technical/images/technical/CursrA00.png");
    };
    virtual QPixmap pixmap(int) = 0;
    virtual bool interactive(Color&) = 0;
    virtual QPoint offset() = 0;
    int x;
    int y;
};

class Stone : public Object
{
public:
    Stone(int newx, int newy){x = newx; y = newy;}
    QString writeLog() const override{
        return QString("Камень (").append(QString::number(x)).append(", ").append(QString::number(y)).append(") - Взаимодействие\n");
    }
    QString statusBar() override{
        return "Камень";
    }
    QPixmap pixmap(int passability) override{
        if(passability == 2)
            return QPixmap(":/landscape/images/landscape/AVLrk400.png");
        return QPixmap();
    }
    bool interactive(Color& color) override{notify(); return false;}
    QPoint offset() override{
        return QPoint(0, 0);
    }
};

class Bonfire : public Object
{
public:
    int animation = 0;
    Bonfire(int newx, int newy){x = newx; y = newy;}
    QString writeLog() const override{
        return QString("Костер (").append(QString::number(x)).append(", ").append(QString::number(y)).append(") - Взаимодействие\n");
    }
    QString statusBar() override{
        return "Костер";
    }
    QPixmap pixmap(int passability) override{
        if(passability == 1){
            if(animation == 8)
                animation = 0;
            return QPixmap(":/objects/images/objects/bonfire.png").copy(0+(32*animation++), 0, 32, 32);
        }
        return QPixmap();
    }
    bool interactive(Color& color) override{
        QSound::play(":/technical/sounds/technical/PICKUP01.wav");
        color.gold+= 500;
        notify();
        return false;
    }
    QPoint offset() override{
        return QPoint(0, 0);
    }
};

class Castle : public Object
{
public:
    int color;
    Castle(int newcolor, int newx, int newy){color = newcolor; x = newx; y = newy;}
    QString writeLog() const override{
        return QString("Замок (").append(QString::number(x)).append(", ").append(QString::number(y)).append(") - Взаимодействие\n");
    }
    QString statusBar() override{
        return "Замок";
    }
    QPixmap pixmap(int passability) override{
        if(passability == 1)
            return QPixmap(":/objects/images/objects/castle/AVCcasx0.png");
        else
            return QPixmap();
    }
    bool interactive(Color& colorHero) override{
        QSound::play(":/technical/sounds/technical/BUILDTWN.WAV");
        notify();
        return false;
    };
    QPoint offset() override{
        return QPoint(-32*3, -32*5);
    }
};

class Stronghold : public Object
{
public:
    int color;
    Stronghold(int newcolor, int newx, int newy){color = newcolor; x = newx; y = newy;}
    QString writeLog() const override{
        return QString("Цитадель (").append(QString::number(x)).append(", ").append(QString::number(y)).append(") - Взаимодействие\n");
    }
    QString statusBar() override{
        return "Цитадель";
    }
    QPixmap pixmap(int passability) override{
        if(passability == 1)
            return QPixmap(":/objects/images/objects/castle/AVCstrx0.png");
        else
            return QPixmap();
    }
    bool interactive(Color& color) override{
        QSound::play(":/technical/sounds/technical/BUILDTWN.WAV");
        notify();
        return false;
    }
    QPoint offset() override{
        return QPoint(-32*3, -32*5);
    }
};

class Fortress : public Object
{
public:
    int color;
    Fortress(int newcolor, int newx, int newy){color = newcolor; x = newx; y = newy;}
    QString writeLog() const override{
        return QString("Крепость (").append(QString::number(x)).append(", ").append(QString::number(y)).append(") - Взаимодействие\n");
    }
    QString statusBar() override{
        return "Крепость";
    }
    QPixmap pixmap(int passability) override{
        if(passability == 1)
            return QPixmap(":/objects/images/objects/castle/AVCftrx0.png");
        else
            return QPixmap();
    }
    bool interactive(Color& color) override{
        QSound::play(":/technical/sounds/technical/BUILDTWN.WAV");
         notify();
        if(color.gold>=500)
            return true;
        return false;
    }
    QPoint offset() override{
        return QPoint(-32*3, -32*5);
    }
};

#endif // OBJECT_H
