#ifndef ANALAYZER_H
#define ANALAYZER_H

#include <QObject>
#include<QTcpSocket>
#include<QTcpServer>
#include<QHostAddress>
#include<QString>
#include <QTime>
#include <QDialog>

//#include "ui_mainwindow.h"

//Команда для сохранения в формате csv
//setcommand(":MMEMory:STORe 'C:/pro/"+diapason+".csv' \n");
QT_BEGIN_NAMESPACE

namespace Ui {
class analayzer;
}

QT_END_NAMESPACE


class Analayzer: public QDialog
{
    Q_OBJECT

public:
    explicit Analayzer(QWidget *parent = nullptr);
    ~Analayzer();
    enum Type {
        Anritsu = 0,
        Planar,
        Unknow
    };

    struct Settings {
        QString aver_count;
        QString poin;
        QString start_f;
        QString end_f;
        QString power;
    };

    void updateSettings();

public slots:

    void slt_show(int tf);

    void connectToHost(int tf);
    void setcommand(QString);

    QByteArray readyReadSlot();

    void S21();
    void S12();
    void Pow(QString power);
    void LOGPHase();
    void R1C1();
    void SetFreqStart(QString freq);
    void SetFreqEnd(QString freq);
    void SetFreq(int range);
    void Point(QString point);

    void Hold();
    void Cont();
    void Buff();
    void Div();
    void DispDiv();
    void SaveCSV();

    void Format();
    void Get();
    void Point();
    void Data();
    void AverSWE();
    void AverCLE();
    void AverCOUNT();
    void SetAverCOUNT(QString point);
    void AverTYP();
    void AverON();

    void Memory_store(QString);


private slots:
    void on_applyButton_clicked();

    void on_disconnecnt_btn_clicked();

    void on_Connect_btn_clicked();

private:
    Settings settings;

    void updatesettings();
    void fillPortsParameters();
    void setportsParameters();
    Ui::analayzer *m_ui = nullptr;

    Type type = Type::Planar;

    QString host = "127.0.0.1"; //ip нашего устройства
    int port = 5025;// порт устройства

    bool connected = false;
    QTcpSocket* socket;

    QStringList freq ={"4.5E9", "18E9",
                          "4.5E9", "8E9",
                          "8E9", "11.5E9",
                          "11.5E9", "15E9",
                          "15E9", "18E9"
                         };
};

#endif // ANALAYZER_H
