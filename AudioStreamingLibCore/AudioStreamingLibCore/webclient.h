#ifndef WEBCLIENT_H
#define WEBCLIENT_H

#include "abstractclient.h"
#include "openssllib.h"
#include "sslclient.h"
#include "common.h"

class WebClient : public AbstractClient
{
    Q_OBJECT
public:
    explicit WebClient(QObject *parent = nullptr);
    ~WebClient();

public slots:
    void abort();
    void connectToHost(const QString &host, quint16 port,
                       const QByteArray &negotiation_string,
                       const QString &id,
                       const QByteArray &password,
                       bool new_user);
    void connectToPeer(const QString &peer_id);
    void disconnectFromPeer();
    void stop();
    int write(const QByteArray &data);
    void acceptConnection();
    void rejectConnection();
    void acceptSslCertificate();

private slots:
    bool testSsl();
    void connectedToServerPrivate(const QByteArray &hash);
    void disconnectedFromServer();
    void pendingPrivate(quint32 host, const QByteArray &id);
    void connectedToPeerPrivate(const QByteArray &id, const QByteArray &password);
    void disconnectedFromPeerPrivate();
    void readyReadPrivate(const QByteArray &data);

private:
    qintptr m_descriptor;
    bool m_ssl_certificate_accepted;
    OpenSslLib *m_openssl;
    SslClient *m_ssl_client;
    QByteArray m_negotiation_string;
    QString m_id;
    QByteArray m_password;
    bool m_new_user;
    QByteArray m_peer_id;
};

#endif // WEBCLIENT_H
