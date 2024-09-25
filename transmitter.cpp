#include "transmitter.h"

Transmitter::Transmitter(QString ip_dst, int port_dst) : QObject{nullptr}
{
    this->ip_dst = ip_dst;
    this->port_dst = port_dst;
}

void Transmitter::init()
{
    if(socket == nullptr) {
        socket = new QTcpSocket(this);
//        socket->connectToHost(ip_dst,port_dst);
//        if (!socket->waitForConnected(3000)){
//            // Устанавливаем иконку ошибки
//            msgBox.setIcon(QMessageBox::Critical);

//            // Устанавливаем заголовок окна
//            msgBox.setWindowTitle("Ошибка подключения");

//            // Устанавливаем текст сообщения
//            msgBox.setText("Проблемы с подключением. Проверьте соединение и повторите попытку.");

//            // Отображаем сообщение
//            msgBox.exec();
//        }
    }
}

Transmitter::~Transmitter()
{
    if(socket != nullptr) {
        delete socket;
    }
}


void Transmitter::send(QString& cmd) {

    socket->write(cmd.toLocal8Bit());
}

void Transmitter::setAddress(QString ip_dst, int port_dst) {

    this->ip_dst = ip_dst;
    this->port_dst = port_dst;

    socket->connectToHost(ip_dst,port_dst);
    if (!socket->waitForConnected(3000)){
        // Устанавливаем иконку ошибки
        msgBox.setIcon(QMessageBox::Critical);

        // Устанавливаем заголовок окна
        msgBox.setWindowTitle("Ошибка подключения");

        // Устанавливаем текст сообщения
        msgBox.setText("Проблемы с подключением. Проверьте соединение и повторите попытку.");

        // Отображаем сообщение
        msgBox.exec();
    }
}
