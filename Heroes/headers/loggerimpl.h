#ifndef LOGGERIMPL_H
#define LOGGERIMPL_H
#include "logsubscriber.h"

class LoggerImpl{
public:
    virtual ~LoggerImpl(){}
    virtual void Console_log(LogPublisher& publisher) = 0;
    virtual void File_log(LogPublisher& publisher, std::ostream& file) = 0;
};

class BlueColorLog : public LoggerImpl{
public:
    BlueColorLog(){}
    ~BlueColorLog() override{}
    void Console_log(LogPublisher& publisher) override{
        std::cout << "Синий: ";
        std::cout << publisher;
    }
    void File_log(LogPublisher &publisher, std::ostream &file) override{
        file << "Синий: ";
        file << publisher;
    }
};

#endif // LOGGERIMPL_H
