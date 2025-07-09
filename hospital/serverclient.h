#ifndef SERVERCLIENT_H
#define SERVERCLIENT_H

#include <QString>
#include <QStringList>

class ServerClient
{
public:
    ServerClient(const QString& host, quint16 port);
    ~ServerClient();

    // Envía una consulta SQL al servidor y devuelve la respuesta como lista de líneas
    QStringList sendQuery(const QString& query);

private:
    QString m_host;
    quint16 m_port;
};

#endif // SERVERCLIENT_H
