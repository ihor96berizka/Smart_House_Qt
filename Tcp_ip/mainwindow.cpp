#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "constants.h"
#include "qdeviceconfigview.h"
#include <QLabel>
#include <QMenuBar>
#include <QComboBox>
#include <QVBoxLayout>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    createActions();
    createMenu();
    // mainWindget = new QStackedWidget(this);
    QWidget* centerWidget = new QWidget(this);
    settingsView = new QDeviceConfigView(centerWidget);

    setCentralWidget(settingsView);
    connect(settingsView, &QDeviceConfigView::dataSaved, this, &MainWindow::getDeviceConfigSlot);
    // QLabel* testWindow = new QLabel(this);
    // testWindow->setText("second window");
    m_tcpSocket = new QTcpSocket(this);
    connect(m_tcpSocket, &QTcpSocket::readyRead, this, &MainWindow::readDataFromServer);
    // mainWindget->addWidget(view);
    // mainWindget->addWidget(testWindow);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createActions()
{
    openConfigDeviceViewAct = new QAction(tr("Open"), this);
    openConfigDeviceViewAct->setStatusTip(QStringLiteral("Open device configuration menu"));
    connect(openConfigDeviceViewAct, &QAction::triggered, this, &MainWindow::openConfigDeviceViewSlot);

    connectToServerAct = new QAction(tr("Connect"), this);
    connect(connectToServerAct, &QAction::triggered, this, &MainWindow::connectToServerSlot);

    disconnectFromServerAct = new QAction(tr("Disconnect"), this);
    connect(disconnectFromServerAct, &QAction::triggered, this, &MainWindow::disconnectFromServerSlot);

    uploadWiFiConfigToServerAct = new QAction(tr("Upload Wifi config"), this);
    connect(uploadWiFiConfigToServerAct, &QAction::triggered, this, &MainWindow::uploadWiFiConfigToServerSlot);
    uploadMQTTConfigToServerAct = new QAction(tr("Upload MQTT config"), this);
    connect(uploadMQTTConfigToServerAct, &QAction::triggered, this, &MainWindow::uploadMQTTConfigToServerSlot);
}

void MainWindow::createMenu()
{
    configurationMenu = menuBar()->addMenu(tr("Configure device"));
    configurationMenu->addActions({openConfigDeviceViewAct});

    serverMenu = menuBar()->addMenu(tr("Server"));
    serverMenu->addActions({connectToServerAct, disconnectFromServerAct,
                            uploadWiFiConfigToServerAct, uploadMQTTConfigToServerAct});
}

QByteArray MainWindow::genPacket(DeviceConfig& data, const uint8_t type) const
{
    QByteArray packet;
    switch (type) {
    case WIFI_CONFIG:
    {
        packet.append(WIFI_CONFIG);
        //+1 - бо ще треба врахувати SEPARATOR
        uint16_t data_len = data.wifi_ssid().size() + data.wifi_pwd().size() + 1;
        uint8_t len_MSB = data_len << 8;
        uint8_t len_LSB = data_len & 0xFF;

        packet.append(len_MSB);
        packet.append(len_LSB);
        packet.append(data.wifi_ssid() +
                      DATA_SEPARATOR +
                    data.wifi_pwd());
    }
        break;
    case MQTT_CONFIG:
    {
        packet.append(MQTT_CONFIG);
        //+3 - бо ще треба врахувати SEPARATOR
        uint16_t data_len = data.server_name().size() + QString::number(data.server_port()).size() +
                + data.server_user().size() + data.server_pwd().size() + 3;
        uint8_t len_MSB = data_len << 8;
        uint8_t len_LSB = data_len & 0xFF;

        packet.append(len_MSB);
        packet.append(len_LSB);
        packet.append(data.server_name() +
                      DATA_SEPARATOR +
                     QString::number(data.server_port()) +
                      DATA_SEPARATOR +
                      data.server_user() +
                      DATA_SEPARATOR +
                      data.server_pwd());
    }
        break;
    default:
    {
        QMessageBox msg;
        msg.setText("Unknown packet type!");
        msg.exec();
    }
        break;
    }
    return std::move(packet);
}

void MainWindow::getDeviceConfigSlot(DeviceConfig data)
{
    this->m_config = data;
    QMessageBox msg;
    msg.setText(QStringLiteral("Config saved...") + data.wifi_ssid()
                + "\t" + data.wifi_pwd());
    msg.exec();
}

void MainWindow::openConfigDeviceViewSlot()
{

}

void MainWindow::connectToServerSlot()
{


    // m_serverAddr = QHostAddress("10.42.0.174");
    m_serverPort = 80;
    m_tcpSocket->connectToHost(QHostAddress("192.168.4.1"), m_serverPort);
    if (m_tcpSocket->waitForConnected(5000))
    {
        QMessageBox message;
        message.setText("Connected to server!");
        message.exec();
    }
    else
    {
        QMessageBox message;
        message.setText(m_tcpSocket->errorString());
        message.exec();
    }
}

void MainWindow::disconnectFromServerSlot()
{
    m_tcpSocket->disconnectFromHost();
}

void MainWindow::uploadWiFiConfigToServerSlot()
{
    //готовий пакет. тільки надіслати
    QByteArray data = genPacket(m_config, WIFI_CONFIG);
    //довжина пакету шо надсилаємо
    const size_t PACKET_LEN = data.size();
    if (m_tcpSocket->state() == QAbstractSocket::ConnectedState)
    {
        m_tcpSocket->write(data, PACKET_LEN);
        QMessageBox message;
        message.setText("Done!(WifiConfig)");
        message.exec();
    }
}

void MainWindow::uploadMQTTConfigToServerSlot()
{
    //готовий пакет. тільки надіслати
    QByteArray data = genPacket(m_config, MQTT_CONFIG);
    //довжина пакету шо надсилаємо
    const size_t PACKET_LEN = data.size();
    if (m_tcpSocket->state() == QAbstractSocket::ConnectedState)
    {
        m_tcpSocket->write(data, PACKET_LEN);
        QMessageBox message;
        message.setText("Done!(MQTT config)");
        message.exec();
    }
}

void MainWindow::readDataFromServer()
{
    QDataStream in(m_tcpSocket);
    uint8_t current_value = 0;
    in >> current_value;
    QString message;
    if (current_value == WIFI_ERROR)
    {
        message = "Invalid SSID or password!";
    }
    QMessageBox msg;
    msg.setText(message);
    msg.exec();
}
