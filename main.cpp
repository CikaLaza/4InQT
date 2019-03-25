#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickWindow>

#include "qmlconnector.h"
#include "qmlresponsehandler.h"


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    SharedQueue<int> queue;

    QMLResponsehandler reader;
    reader.setQueue(&queue);
    reader.start();

    QMLConnector connector;
    connector.setQueue(&queue);

    QObject *mainQMLbject = engine.rootObjects().value(0);
    QQuickWindow *window = qobject_cast<QQuickWindow *>(mainQMLbject);

    QObject::connect(window, SIGNAL(onTableClick(int)), &connector, SLOT(onTableClick(int)));
    QObject::connect(&reader, SIGNAL(movePlayed(int, int, int)), window, SIGNAL(movePlayed(int, int, int)));
    QObject::connect(&reader, SIGNAL(victory(int)), window, SIGNAL(victory(int)));

    return app.exec();
}
