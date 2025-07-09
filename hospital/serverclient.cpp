#include "serverclient.h"
#include <QTcpSocket>

ServerClient::ServerClient(const QString& host, quint16 port)
    : m_host(host), m_port(port)
{
}

ServerClient::~ServerClient() {}

QStringList ServerClient::sendQuery(const QString& query)
{
    QTcpSocket socket;
    socket.connectToHost(m_host, m_port);
    if (!socket.waitForConnected(2000)) {
        return {"ERROR: No se pudo conectar al servidor"};
    }
    socket.write(query.toUtf8() + '\n');
    socket.flush();
    if (!socket.waitForReadyRead(3000)) {
        return {"ERROR: Sin respuesta del servidor"};
    }
    QByteArray response = socket.readAll();
    socket.disconnectFromHost();
    return QString(response).split('\n', Qt::SkipEmptyParts);
}
