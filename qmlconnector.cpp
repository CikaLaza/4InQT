#include "qmlconnector.h"

QMLConnector::QMLConnector(QObject *parent) : QObject(parent)
{
}

void QMLConnector::onTableClick(int param)
{
    int column = param % COLS;
    qDebug() << __FUNCTION__ << "@" << __LINE__ << " " << column;
    queue->push_back(column);
}
