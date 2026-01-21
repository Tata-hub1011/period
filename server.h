#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QMap>

struct UserInfo {
    QString nickname;
    bool isBanned = false;
};

class ChatServer : public QTcpServer {
    Q_OBJECT
public:
    explicit ChatServer(QObject *parent = nullptr);
    void disconnectUser(int socketDescriptor);
    void banUser(const QString &ip);

signals:
    void logMessage(const QString &msg);
    void userListUpdated(const QStringList &users);

protected:
    void incomingConnection(qintptr socketDescriptor) override;

private slots:
    void onReadyRead();
    void onDisconnected();

private:
    void sendToAll(const QJsonObject &doc);
    QMap<QTcpSocket*, UserInfo> clients;
    QStringList bannedIPs;
};




#endif
