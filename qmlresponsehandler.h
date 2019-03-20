#pragma once

#include <QObject>
#include <QDebug>
#include<thread>

#include "board.h"
#include "sharedqueue.h"


class QMLResponsehandler : public QObject
{
    Q_OBJECT
public:
    QMLResponsehandler(QObject *parent = nullptr);
    ~QMLResponsehandler();

    void setQueue(SharedQueue<int>*);
    void loop();
    void start();

signals:
    void movePlayed(int, int, int);

private:
    SharedQueue<int>* queue;
    std::thread * mainThread;
    bool running;
};
