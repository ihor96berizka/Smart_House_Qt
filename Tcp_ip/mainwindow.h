#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMenu>
#include <QAction>
#include <QTextEdit>
#include <QtNetwork>
#include <QMainWindow>
#include <QStackedWidget>
#include "deviceconfig.h"
class QDeviceConfigView;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow* ui = nullptr;
    QStackedWidget* mainWindget = nullptr;
    QDeviceConfigView* settingsView = nullptr;

    QMenu* configurationMenu = nullptr;
    QMenu* serverMenu = nullptr;
    QAction* openConfigDeviceViewAct = nullptr;
    QAction* connectToServerAct = nullptr;
    QAction* disconnectFromServerAct = nullptr;
    QAction* uploadWiFiConfigToServerAct = nullptr;
    QAction* uploadMQTTConfigToServerAct = nullptr;
    QTextEdit* logs_text = nullptr;
    DeviceConfig m_config;
    QHostAddress m_serverAddr;
    int m_serverPort;
    QTcpSocket* m_tcpSocket = nullptr;

    void createActions();
    void createMenu();
    QByteArray genPacket(DeviceConfig &data, const uint8_t type) const;
private slots:
    //слот для отримання всіх налаштувань від віджета
    void getDeviceConfigSlot(DeviceConfig data);
   //слоти для підключення до есп на обміну даними
    void openConfigDeviceViewSlot();
    void connectToServerSlot();
    void disconnectFromServerSlot();
    void uploadWiFiConfigToServerSlot();
    void uploadMQTTConfigToServerSlot();
    void readDataFromServer();
};

#endif // MAINWINDOW_H
