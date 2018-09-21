#include "qdeviceconfigview.h"

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

void QDeviceConfigView::createWidgets()
{
    auto layout_main = new QVBoxLayout(this);
    this->setLayout(layout_main);

    auto layout_ssid = new QHBoxLayout();
    auto label_ssid = new QLabel(this);
    text_ssid = new QLineEdit(this);
    text_ssid->setFixedHeight(fixHeight);
    label_ssid->setText(QStringLiteral("WiFi ssid: "));
    layout_ssid->addWidget(label_ssid, 0, Qt::AlignCenter);
    layout_ssid->addWidget(text_ssid, 0, Qt::AlignCenter);

    layout_main->addLayout(layout_ssid);

    auto layout_pwd = new QHBoxLayout();
    auto label_pwd = new QLabel(this);
    text_pwd = new QLineEdit(this);
    text_pwd->setFixedHeight(fixHeight);
    label_pwd->setText(QStringLiteral("WiFi password: "));
    layout_pwd->addWidget(label_pwd, 0, Qt::AlignCenter);
    layout_pwd->addWidget(text_pwd, 0, Qt::AlignCenter);

    layout_main->addLayout(layout_pwd);

    auto layout_mqtt = new QHBoxLayout();
    auto label_mqtt = new QLabel(this);
    label_mqtt->setText("MQTT config");
    layout_mqtt->addWidget(label_mqtt, 0, Qt::AlignCenter);
    layout_mqtt->setDirection(QBoxLayout::LeftToRight);

    layout_main->addLayout(layout_mqtt);

    auto layout_server_name = new QHBoxLayout();
    auto label_server_name = new QLabel(this);
    text_server_name = new QLineEdit(this);
    text_server_name->setFixedHeight(fixHeight);
    label_server_name->setText(QStringLiteral("server: "));
    layout_server_name->addWidget(label_server_name, 0, Qt::AlignCenter);
    layout_server_name->addWidget(text_server_name, 0, Qt::AlignCenter);

    layout_main->addLayout(layout_server_name);

    auto layout_server_port = new QHBoxLayout();
    auto label_server_port = new QLabel(this);
    text_server_port = new QLineEdit(this);
    text_server_port->setFixedHeight(fixHeight);
    label_server_port->setText(QStringLiteral("port: "));
    layout_server_port->addWidget(label_server_port, 0, Qt::AlignCenter);
    layout_server_port->addWidget(text_server_port, 0, Qt::AlignCenter);

    layout_main->addLayout(layout_server_port);

    auto layout_server_user = new QHBoxLayout();
    auto label_server_user = new QLabel(this);
    text_server_user = new QLineEdit(this);
    text_server_user->setFixedHeight(fixHeight);
    label_server_user->setText(QStringLiteral("user: "));
    layout_server_user->addWidget(label_server_user, 0, Qt::AlignCenter);
    layout_server_user->addWidget(text_server_user, 0, Qt::AlignCenter);

    layout_main->addLayout(layout_server_user);

    auto layout_server_pwd = new QHBoxLayout();
    auto label_server_pwd = new QLabel(this);
    text_server_pwd = new QLineEdit(this);
    text_server_pwd->setFixedHeight(fixHeight);
    label_server_pwd->setText(QStringLiteral("password: "));
    layout_server_pwd->addWidget(label_server_pwd, 0, Qt::AlignCenter);
    //layout_server_port->addSpacing(55);
    layout_server_pwd->addWidget(text_server_pwd, 0, Qt::AlignCenter);

    layout_main->addLayout(layout_server_pwd);

    auto buttonSave = new QPushButton(this);
    buttonSave->setText("Save configuration");
    buttonSave->setMinimumSize(90, 50);
    connect(buttonSave, SIGNAL(clicked(bool)), this, SLOT(saveConfig()));
    auto layout_button = new QHBoxLayout();
    layout_button->addWidget(buttonSave, 0, Qt::AlignCenter);

    layout_main->addLayout(layout_button);
}

QDeviceConfigView::QDeviceConfigView(QWidget *parent) : QWidget(parent)
{
    createWidgets();
}

void QDeviceConfigView::saveConfig()
{
   m_data.setWifi_ssid(text_ssid->text());
   m_data.setWifi_pwd(text_pwd->text());
   m_data.setServer_name(text_server_name->text());
   m_data.setServer_port(text_server_port->text().toInt());
   m_data.setServer_user(text_server_user->text());
   m_data.setServer_pwd(text_server_pwd->text());
   emit dataSaved(m_data);
}
