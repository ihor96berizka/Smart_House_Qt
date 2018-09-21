#ifndef DEVICECONFIG_H
#define DEVICECONFIG_H

#include <QString>

class DeviceConfig
{
public:
    DeviceConfig();
    DeviceConfig(const DeviceConfig&) = default;
    DeviceConfig& operator =(const DeviceConfig&) = default;
    QString wifi_ssid() const;
    void setWifi_ssid(const QString &wifi_ssid);

    QString wifi_pwd() const;
    void setWifi_pwd(const QString &wifi_pwd);

    QString server_name() const;
    void setServer_name(const QString &server_name);

    int server_port() const;
    void setServer_port(int server_port);

    QString server_user() const;
    void setServer_user(const QString &server_user);

    QString server_pwd() const;
    void setServer_pwd(const QString &server_pwd);

private:
    QString m_wifi_ssid;
    QString m_wifi_pwd;
    QString m_server_name;
    int m_server_port;
    QString m_server_user;
    QString m_server_pwd;
};

#endif // DEVICECONFIG_H
