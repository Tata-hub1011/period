#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    server = new ChatServer(this);
    
    // UI Layout
    QWidget *central = new QWidget(this);
    QHBoxLayout *mainLayout = new QHBoxLayout(central);

    // Левая панель - логи
    QVBoxLayout *leftLayout = new QVBoxLayout();
    logDisplay = new QTextEdit();
    logDisplay->setReadOnly(true);
    leftLayout->addWidget(new QLabel("Мониторинг сообщений:"));
    leftLayout->addWidget(logDisplay);

    // Правая панель - пользователи
    QVBoxLayout *rightLayout = new QVBoxLayout();
    userList = new QListWidget();
    kickButton = new QPushButton("Кикнуть");
    banButton = new QPushButton("Забанить");
    
    rightLayout->addWidget(new QLabel("Онлайн:"));
    rightLayout->addWidget(userList);
    rightLayout->addWidget(kickButton);
    rightLayout->addWidget(banButton);

    mainLayout->addLayout(leftLayout, 3);
    mainLayout->addLayout(rightLayout, 1);
    setCentralWidget(central);

    // Стилизация (Тёмная тема)
    this->setStyleSheet("QMainWindow { background-color: #2b2b2b; color: white; }"
                        "QTextEdit, QListWidget { background-color: #3c3f41; color: #bbbeff; border: 1px solid #555; border-radius: 5px; }"
                        "QPushButton { background-color: #4b6eaf; color: white; padding: 5px; border-radius: 3px; }"
                        "QPushButton:hover { background-color: #5b7ebf; }");

    connect(server, &ChatServer::logMessage, this, &MainWindow::appendLog);
    
    if (!server->listen(QHostAddress::Any, 1234)) {
        logDisplay->append("Ошибка запуска сервера!");
    } else {
        logDisplay->append("Сервер запущен на порту 1234...");
    }
}

void MainWindow::appendLog(const QString &msg) {
    logDisplay->append(msg);
}

void MainWindow::updateUsers(const QStringList &users) {
    userList->clear();
    userList->addItems(users);
}

void MainWindow::onKickClicked() {
    // Логика получения выбранного пользователя и вызов server->disconnectUser
}


