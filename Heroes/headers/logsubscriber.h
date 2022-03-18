#ifndef LOGSUBSCRIBER_H
#define LOGSUBSCRIBER_H
#include "logpublisher.h"
#include <iostream>
#include <fstream>

class LogPublisher;
class LogSubscriber{
public:
    virtual ~LogSubscriber(){};
    virtual void Update(LogPublisher& publisher) = 0;
};


#endif // LOGSUBSCRIBER_H
