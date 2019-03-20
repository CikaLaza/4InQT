#include "qmlresponsehandler.h"

QMLResponsehandler::QMLResponsehandler(QObject *parent)
    : QObject(parent),
      mainThread(nullptr),
      running(false)
{
}


QMLResponsehandler::~QMLResponsehandler() {
    running = false;
    mainThread->join();
    delete mainThread;
    qDebug() << __FUNCTION__ << "@" << __LINE__ << " EXIT";
}

void QMLResponsehandler::loop()
{
    running = true;
    while(running)
    {
        if(!queue->empty())
        {
            int value = queue->front();
            queue->pop_front();
            qDebug() << __FUNCTION__ << "@" << __LINE__ << " " << value;

            Board::Players player = Board::getInstance().getActivePlayer();
            int row = Board::getInstance().getRow(value);
            if (row >= 0)
            {
                Board::getInstance().playMove(row, value, player);
                Board::getInstance().switchPlayer();
            }
            else {
                // error
            }
            emit movePlayed(value, row, (int)player);
        }
    }
}

void QMLResponsehandler::start() {

    mainThread = new std::thread(&QMLResponsehandler::loop, this);
}

void QMLResponsehandler::setQueue(SharedQueue<int>* param) {
    queue = param;
}
