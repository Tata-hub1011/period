#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QTextEdit>
#include <QPushButton>
#include "server.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void appendLog(const QString &msg);
    void updateUsers(const QStringList &users);
    void onKickClicked();

private:
    ChatServer *server;
    QTextEdit *logDisplay;
    QListWidget *userList;
    QPushButton *kickButton;
    QPushButton *banButton;
};

#endif



