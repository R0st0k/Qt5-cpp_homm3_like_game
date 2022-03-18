#ifndef KEYCOMMAND_H
#define KEYCOMMAND_H
#include "gameview.h"

class KeyCommand{
public:
    virtual void Execute(GameView*) = 0;
    virtual ~KeyCommand(){}
};

class LeftKeyCommand : public KeyCommand{
public:
    void Execute(GameView* view) override{
        view->keyPressChange(-1, 0);
    }
    virtual ~LeftKeyCommand(){}
};

class RightKeyCommand : public KeyCommand{
public:
    void Execute(GameView* view) override{
        view->keyPressChange(1, 0);
    }
    virtual ~RightKeyCommand(){}
};

class UpKeyCommand : public KeyCommand{
public:
    void Execute(GameView* view) override{
        view->keyPressChange(0, -1);
    }
    virtual ~UpKeyCommand(){}
};

class DownKeyCommand : public KeyCommand{
public:
    void Execute(GameView* view) override{
        view->keyPressChange(0, 1);
    }
    virtual ~DownKeyCommand(){}
};

#endif // KEYCOMMAND_H
