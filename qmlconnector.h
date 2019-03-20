#ifndef QMLCONNECTOR_H
#define QMLCONNECTOR_H

#include <QObject>
#include <QDebug>
#include "sharedqueue.h"

class QMLConnector : public QObject
{
    Q_OBJECT
public:

    const static short ROWS = 6;
    const static short COLS= 7;

    QMLConnector(QObject *parent = nullptr);

    void setQueue(SharedQueue<int>* param) {
        queue = param;
    }

signals:
    void playMove(int, int);

public slots:
    void onTableClick(int);

private:
    SharedQueue<int>* queue;
};

#endif // QMLCONNECTOR_H
