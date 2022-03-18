#ifndef COLORLOGGER_H
#define COLORLOGGER_H
#include "headers/loggerimpl.h"

class LoggerImpl;

class ColorLogger : public LogSubscriber{
public:
    ColorLogger(LoggerImpl* p):pimpl(p){}
    ~ColorLogger(){delete pimpl;}
    virtual void Update(LogPublisher& publisher) = 0;
protected:
    LoggerImpl * pimpl;
};

class ConsoleColorLogger : public ColorLogger{
public:
    ConsoleColorLogger(int color):ColorLogger(new BlueColorLog){}
    void Update(LogPublisher &publisher) override{
        pimpl->Console_log(publisher);
    }
};

class FileColorLogger : public ColorLogger{
public:
    FileColorLogger(int color):ColorLogger(new BlueColorLog){logfile.open("/home/rostislav/log.txt");}
    ~FileColorLogger(){if(logfile.is_open())logfile.close();}
    void Update(LogPublisher &publisher) override{
        pimpl->File_log(publisher, logfile);
    }
private:
    std::ofstream logfile;
};

#endif // COLORLOGGER_H
