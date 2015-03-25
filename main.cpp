#include <QApplication>
#include <QQmlApplicationEngine>
#include "udpbroadcast.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    QObject *rootObject = engine.rootObjects().first();
    QObject *sendButton = rootObject->findChild<QObject*>("sendButton");
    QObject *chatText = rootObject->findChild<QObject*>("chatText");

    UDPBroadcast udpBroadcast;

    QObject::connect(sendButton, SIGNAL(notifyClick(QString)), &udpBroadcast, SLOT(broadcastMessage(QString)));
    QObject::connect(&udpBroadcast, SIGNAL(notifyNewMessage(QVariant)), chatText, SLOT(updateChat(QVariant)));

    return app.exec();
}
