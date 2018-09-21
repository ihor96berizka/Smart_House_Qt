#include "deviceconfig.h"

DeviceConfig::DeviceConfig()
{

}

QString DeviceConfig::wifi_ssid() const
{
    return m_wifi_ssid;
}

void DeviceConfig::setWifi_ssid(const QString &wifi_ssid)
{
    m_wifi_ssid = wifi_ssid;
}

QString DeviceConfig::wifi_pwd() const
{
    return m_wifi_pwd;
}

void DeviceConfig::setWifi_pwd(const QString &wifi_pwd)
{
    m_wifi_pwd = wifi_pwd;
}

QString DeviceConfig::server_name() const
{
    return m_server_name;
}

void DeviceConfig::setServer_name(const QString &server_name)
{
    m_server_name = server_name;
}

int DeviceConfig::server_port() const
{
    return m_server_port;
}

void DeviceConfig::setServer_port(int server_port)
{
    m_server_port = server_port;
}

QString DeviceConfig::server_user() const
{
    return m_server_user;
}

void DeviceConfig::setServer_user(const QString &server_user)
{
    m_server_user = server_user;
}

QString DeviceConfig::server_pwd() const
{
    return m_server_pwd;
}

void DeviceConfig::setServer_pwd(const QString &server_pwd)
{
    m_server_pwd = server_pwd;
}
