#ifndef LOGPUBLISHER_H
#define LOGPUBLISHER_H
#include "logsubscriber.h"
#include <QList>

class LogPublisher{
public:
    virtual ~LogPublisher(){};
    void subscribe(LogSubscriber* sub){
        subscriberList.append(sub);
    }
    void unsubscribe(LogSubscriber* sub){
        subscriberList.removeOne(sub);
    }
    void notify(){
        QList<LogSubscriber*>::iterator i;
        for (i = subscriberList.begin(); i != subscriberList.end(); ++i)
            i.operator*()->Update(*this);
    }
    virtual QString writeLog() const = 0;

    friend std::ostream& operator<<(std::ostream& stream, const LogPublisher& rec) {
        stream << rec.writeLog().toStdString();
        return stream;
    }

private:
    QList<LogSubscriber*> subscriberList;
};

#endif // LOGPUBLISHER_H
