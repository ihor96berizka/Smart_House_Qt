#ifndef QDEVICECONFIGVIEW_H
#define QDEVICECONFIGVIEW_H

#include <QWidget>
#include "deviceconfig.h"
class QLineEdit;

class QDeviceConfigView : public QWidget
{
    Q_OBJECT
public:
    explicit QDeviceConfigView(QWidget *parent = nullptr);

signals:
    void dataSaved(DeviceConfig data);
public slots:

private:
    DeviceConfig m_data;
    QLineEdit* text_ssid = nullptr;
    QLineEdit* text_pwd = nullptr;
    QLineEdit* text_server_name = nullptr;
    QLineEdit* text_server_port = nullptr;
    QLineEdit* text_server_user = nullptr;
    QLineEdit* text_server_pwd = nullptr;

    const int fixHeight = 30;
    void createWidgets();

private slots:
    void saveConfig();
};

#endif // QDEVICECONFIGVIEW_H
