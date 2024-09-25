#ifndef TRANSMITTER_H
#define TRANSMITTER_H

#include <QObject>
#include <QTcpSocket>
#include <QMessageBox>

class Transmitter : public QObject
{
    Q_OBJECT

    QTcpSocket *socket{nullptr};

    QString ip_dst;
    int     port_dst;
    QMessageBox msgBox;

public:
    explicit Transmitter(QString ip_dst, int port_dst);
    ~Transmitter();

private slots:
    void init();

    void send(QString& pack);

    void setAddress(QString ip_dst, int port_dst);

signals:

};

#endif // TRANSMITTER_H
