#include "mainwindow.h"

#include <QApplication>
#include <QMessageBox>
#include <QThread>
#include <QtSerialPort/QSerialPort>
#include "bit_manipulation.h"
#include <algorithm>
#include "settingsdialog.h"
#include "analayzer.h"
#include <string>
#include<iostream>
#include<array>
#include "transmitter.h"

void delay(int millisecondsToWait )
{
    QTime dieTime = QTime::currentTime().addMSecs( millisecondsToWait );

    while( QTime::currentTime() < dieTime )
    {
        QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
    }
}



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //Окно основное
    MainWindow mainwindow;
    mainwindow.show();

    //Окно с настройкой тестирования
    Configuration configuration;
    //configuration.show();

    //Настройки подключения по COM порту
    SettingsDialog settingdialog;
    //settingdialog.show();

    //Выходы разьемов на плате
    Connectors connectors;
    //connectors.show();

    Analayzer analayzer;

    //данные для C44020
    //const QString IP_TX = "127.0.0.1";
    //const int PORT_TX = 5025;

    //Если выбран Anritsu меняем
//    if(mainwindow.ui->cmbType->count()){
//        //данные для Anritsu
//        const QString IP_TX = "129.0.1.29";// требует уточнения я забыл что тут было
//        const int PORT_TX = 5001;
//    }

    // Передатчик
//    QThread threadTransmitter;
//    Transmitter transmitter(IP_TX, PORT_TX);
    //settingdialog.moveToThread(&threadTransmitter);

    //QObject::connect(&threadTransmitter, SIGNAL(started()), &transmitter, SLOT(init()));

    //Коннекты для прием передачи по COM  порту
    QObject::connect(&mainwindow, SIGNAL(sgn_open_serialport()), &settingdialog, SLOT(openSerialPort()));
    QObject::connect(&mainwindow, SIGNAL(sgn_close_serialport()), &settingdialog, SLOT(closeSerialPort()));
    QObject::connect(&mainwindow, SIGNAL(sgn_read_serialport()), &settingdialog, SLOT(readData()));
    QObject::connect(&mainwindow, SIGNAL(sgn_write_serialport(QByteArray)), &settingdialog, SLOT(writeData(QByteArray)));
    QObject::connect(&settingdialog, SIGNAL(sgn_append_data(QByteArray)), &mainwindow, SLOT(filltxtoutput(QByteArray)));

    //для отображения информаци о подключении
    QObject::connect(&settingdialog, SIGNAL(sgn_show_StatusMessage(QString)), &mainwindow, SLOT(showStatusMessage(QString)));

    //
    QObject::connect(&mainwindow, SIGNAL(sgn_show_settingdialog()), &settingdialog, SLOT(slt_show()));

    //
    QObject::connect(&mainwindow, SIGNAL(sgn_open_tcpsocket(int)), &analayzer, SLOT(connectToHost(int)));
    QObject::connect(&mainwindow, SIGNAL(sgn_show_analayzer(int)),&analayzer,SLOT(slt_show(int)));

    //
    QObject::connect(&mainwindow, SIGNAL(sgn_setcommand(QString)),&analayzer,SLOT(setcommand(QString)));
    QObject::connect(&mainwindow, SIGNAL(sgn_hold_analayzer()),&analayzer,SLOT(Hold()));
    QObject::connect(&mainwindow, SIGNAL(sgn_cont_analayzer()),&analayzer,SLOT(Cont()));

    //
    QObject::connect(&mainwindow, SIGNAL(sgn_S12()),&analayzer,SLOT(S12()));

    //sdadasdad
    QObject::connect(&mainwindow, SIGNAL(sgn_S21()),&analayzer,SLOT(S21()));
    QObject::connect(&mainwindow, SIGNAL(sgn_freq_range(int)),&analayzer,SLOT(SetFreq(int)));
    QObject::connect(&mainwindow, SIGNAL(sgn_memory_store(QString)),&analayzer,SLOT(Memory_store(QString)));



//    threadTransmitter.start(QThread::NormalPriority);
//    threadTransmitter.quit();
//    threadTransmitter.wait();

    return a.exec();
}
