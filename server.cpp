#include "server.h"
#include <QDateTime>

ChatServer::ChatServer(QObject *parent) : QTcpServer(parent) {}

void ChatServer::incomingConnection(qintptr socketDescriptor) {
    QTcpSocket *socket = new QTcpSocket(this);
    socket->setSocketDescriptor(socketDescriptor);

    if (bannedIPs.contains(socket->peerAddress().toString())) {
        socket->disconnectFromHost();
        return;
    }

    connect(socket, &QTcpSocket::readyRead, this, &ChatServer::onReadyRead);
    connect(socket, &QTcpSocket::disconnected, this, &ChatServer::onDisconnected);

    clients[socket] = UserInfo{"Guest_" + QString::number(socketDescriptor)};
    emit logMessage("Новое подключение: " + QString::number(socketDescriptor));
}

void ChatServer::onReadyRead() {
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
    QByteArray data = socket->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject obj = doc.object();

    QString type = obj["type"].toString();
    if (type == "message") {
        QString text = obj["text"].toString();
        QString senderNick = clients[socket].nickname;
        
        emit logMessage(QString("[%1] %2: %3").arg(QDateTime::currentDateTime().toString("HH:mm"), senderNick, text));
        sendToAll(obj);
    } else if (type == "login") {
        clients[socket].nickname = obj["nickname"].toString();
        emit userListUpdated(QStringList(clients.values().size())); // Упрощенно
    }
}

void ChatServer::sendToAll(const QJsonObject &obj) {
    QByteArray data = QJsonDocument(obj).toJson();
    for (auto s : clients.keys()) {
        s->write(data);
    }
}

void ChatServer::onDisconnected() {
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
    clients.remove(socket);
    socket->deleteLater();
    emit logMessage("Пользователь отключился");
}

void ChatServer::disconnectUser(int socketDescriptor) {
    // Поиск и отключение сокета
}

void ChatServer::banUser(const QString &ip) {
    bannedIPs << ip;
}


