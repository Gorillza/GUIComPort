#include"analayzer.h"
#include "mainwindow.h"
#include "ui_analayzer.h"
#include <QTime>
#include <QDir>
//Конструктор
Analayzer::Analayzer(QWidget *parent):
    m_ui(new Ui::analayzer)
    ,socket(new QTcpSocket)
{
    m_ui->setupUi(this);
}

//Деструктор
Analayzer::~Analayzer(){
    //saveParam();
    delete m_ui;
}

//Слот для действий при нажатии на кнопку
void Analayzer::on_applyButton_clicked(){
    updatesettings();
    setportsParameters();
    setcommand(":CALC:TRAC1:MATH:MEM;:CALC:TRAC2:MATH:MEM;:CALC:TRAC3:MATH:MEM;:CALC:TRAC4:MATH:MEM\n");
    delay(1000);
    setcommand(":CALC:TRAC1:MATH:FUNC DIVide;:CALC:TRAC2:MATH:FUNC DIVide;:CALC:TRAC3:MATH:FUNC DIVide;:CALC:TRAC4:MATH:FUNC DIVide\n");
}

//Слот для показа GUI и заполнения
void Analayzer::slt_show(){
    showNormal();
    activateWindow();
    fillPortsParameters();
}

//------------------------------------------------------------------------------------
//Функции обнавления и заполнения данных в текстовые поля
void Analayzer::updatesettings(){
    settings.start_f    = m_ui->start_freq->text();
    settings.end_f      = m_ui->end_freq->text();
    settings.poin       = m_ui->step_freq->text();
    settings.aver_count = m_ui->avareg_count->text();
    settings.power      = m_ui->power->text();
}

void Analayzer::fillPortsParameters(){
    m_ui->start_freq    ->setText(settings.start_f);
    m_ui->end_freq      ->setText(settings.end_f);
    m_ui->avareg_count  ->setText(settings.aver_count);
    m_ui->step_freq     ->setText(settings.poin);
    m_ui->power         ->setText(settings.power);
}

void Analayzer::setportsParameters(){
    SetFreqStart(settings.start_f);
    SetFreqEnd(settings.end_f);
    Point(settings.poin);
    SetAverCOUNT(settings.aver_count);
    Pow(settings.power);
}
//------------------------------------------------------------------------------------
//База для отправки команд и чтения
void Analayzer::setcommand(QString command){
    socket->write(command.toLocal8Bit());
}

QByteArray Analayzer::readyReadSlot(){
    QByteArray dataArr;
    dataArr = socket->readAll();
    return dataArr;
}
//------------------------------------------------------------------------------------

void Analayzer::connectToHost(int currnttype){
    //socket->disconnectFromHost();

    switch (currnttype) {
        case Type::Anritsu:
            //Anritsu
            type = Type::Anritsu;

            //ip нашего устройства
            host = "172.17.0.29";

            // порт устройства
            port = 5001;

            socket->connectToHost(QHostAddress(host),port);

            SetFreqStart("4.5E9");
            settings.start_f = "4.5E9";

            SetFreqEnd("18E9");
            settings.end_f = "18E9";

            Point("350");
            settings.poin = "350";

            SetAverCOUNT("20");
            settings.aver_count = "20";

            Pow("LOW");
            settings.power = "LOW";

            //Команды для первоначальной настройки
            S21();
            setcommand(":CALC:PAR:COUN 2\n");
            delay(20);
            LOGPHase();
            delay(20);
            R1C1();
            break;
        case Type::Planar:
            //Planar C4420
            type = Type::Planar;

            //ip нашего устройства
            host = "127.0.0.1";

            // порт устройства
            port = 5025;

            socket->connectToHost(QHostAddress(host),port);


            //1. Установить 4 графика
            setcommand(":CALC:PAR:COUN 4\n");

            //Установили чтобы они располагались по схеме номер 8
            setcommand(":DISP:WIND:SPL 8\n");

            //1.1 Амплитуда в лог. масштабе S21.
            //1.2 Фаза S21.
            //1.3 Амплитуда в лог. масштабе S12.
            //1.4 Фаза S12.
            //Установили на первых двух S12 а на вторых двух S21
            setcommand(":CALC:PAR1:DEF S21;:CALC:PAR2:DEF S12;:CALC:PAR3:DEF S21;:CALC:PAR4:DEF S12\n");

            //Установили единицы измерения (фаза и амплитуда лог)
            setcommand(":CALC:TRAC1:FORM MLOGarithmic;:CALC:TRAC2:FORM MLOGarithmic;:CALC:TRAC3:FORM PHAS;:CALC:TRAC4:FORM PHAS\n");

            //2. Установить частотный диапазон, указанный в настройках.
            SetFreqStart("4.5E9");
            settings.start_f = "4.5E9";
            SetFreqEnd("18E9");
            settings.end_f = "18E9";

            //3. Установить мощность, указанную в настройках.
            Pow("0");
            settings.power = "0";

            //4. Установили число точек
            Point("350");
            settings.poin = "350";

            //5. Установка количества измерений (в настройках) для усреднения
            AverON();
            SetAverCOUNT("20");
            settings.aver_count = "20";

            //6. Запомнить состояние графиков и включить «Данные/Память» для всех графиков.
            setcommand(":CALC:TRAC1:MATH:MEM;:CALC:TRAC2:MATH:MEM;:CALC:TRAC3:MATH:MEM;:CALC:TRAC4:MATH:MEM\n");
            setcommand(":CALC:TRAC1:MATH:FUNC DIVide;:CALC:TRAC2:MATH:FUNC DIVide;:CALC:TRAC3:MATH:FUNC DIVide;:CALC:TRAC4:MATH:FUNC DIVide\n");

            //7. ВЧ выход – выкл
            setcommand(":OUTP OFF\n");//для включения setcommand(":OUTP ON\n");

            QDateTime dt2 = QDateTime::currentDateTime();
            //qDebug() << dt2.toString("yyyy_MM_dd");

            QTime dt1 = QTime::currentTime();
            //qDebug() << dt1.toString("hh_mm_ss");

            QString relativePath = "Data/"+dt2.toString("yyyy_MM_dd") + "_" + dt1.toString("hh_mm_ss") + ".csv";
            QString SaveCSV = ":MMEM:STOR:FDAT '" + QDir::currentPath() + "/" + relativePath + "'\n";
            //SaveCSV = ":MMEMory:STORe '\\Turntable\\" + dt2.toString("yyyy_MM_dd") + "_" + dt1.toString("hh_mm_ss") + ".csv'\n";
            qDebug()<<SaveCSV;
            setcommand(SaveCSV);
            break;
    }
}


//Команды которые могут быть использованы исключительно для Anritsu
void Analayzer::R1C1(){
    QString R1C1 = ":DISPlay:WINDow:SPLit R1C1 \n";
    setcommand(R1C1);
}

void Analayzer::LOGPHase(){
    QString LOGPHase = ":CALCulate:PARameter:FORMat LOGPHase \n";
    setcommand(LOGPHase);
}

void Analayzer::Buff(){
    QString Buff = ":CALC:MATH:MEM\n";
    setcommand(Buff);
}
void Analayzer::Div(){
    QString Div = ":CALC:MATH:FUNC DIV\n";
    setcommand(Div);
}
void Analayzer::DispDiv(){
    QString DispDiv = ":CALC:MATH:DISP DMM\n";
    setcommand(DispDiv);
}
void Analayzer::SaveCSV(){
    QString SaveCSV =":MMEMory:STORe 'C:\\result\\name.csv'\n";
    setcommand(SaveCSV);
}

//Команды которые мы разыскали но потом они перестали быть акутальны
void Analayzer::Format(){
    QString Format = ":FORMat:DATA ASCII\n";
    setcommand(Format);
}
void Analayzer::Get(){
    QString Get = "SENS:FREQ:DATA?\n";
    setcommand(Get);
}
void Analayzer::Data(){
    QString Data = ":CALC:DATA:FDAT?\n";
    setcommand(Data);
}

//------------------------------------------------------------------------------------
//активно используемые функции для управления анализатором
void Analayzer::S21(){    
    QString S21 = "";
    switch(type){
        case Type::Anritsu:
            S21 = ":CALC:PAR:DEF S21 \n";
            break;
        case Type::Planar:
            S21 = ":CALC:PAR1:DEF S21;:CALC:PAR2:DEF S21;:CALC:PAR3:DEF S21;:CALC:PAR4:DEF S21\n";  // Остановка индикации
            break;
        case Type::Unknow:
            break;
    }
    setcommand(S21);
}

void Analayzer::S12(){
    QString S12 = "";
    switch(type){
        case Type::Anritsu:
            S12 = ":CALC:PAR:DEF S12 \n";
            break;
        case Type::Planar:
            S12 = ":CALC:PAR1:DEF S12;:CALC:PAR2:DEF S12;:CALC:PAR3:DEF S12;:CALC:PAR4:DEF S12\n";  // Остановка индикации
            break;
        case Type::Unknow:
            break;
    }
    setcommand(S12);
}

void Analayzer::Hold(){
    QString Hold = "";
    switch(type){
        case Type::Anritsu:
            Hold = ":SENSe:HOLD:FUNCtion HOLD\n";
            break;
        case Type::Planar:
            Hold = ":OUTP OFF\n";  // Остановка индикации
            break;
        case Type::Unknow:
            //Hold = hold;
            break;

    }
    setcommand(Hold);
}

void Analayzer::Cont(){
    QString Cont = "";
    switch(type){
        case Type::Anritsu:
            Cont = ":SENSe:HOLD:FUNC CONT\n";
            setcommand(Cont);
            break;
        case Type::Planar:
            Cont = ":OUTP ON\n";  // Продолжение индикации
            setcommand(Cont);
            break;
        case Type::Unknow:
            //Cont = cont;
            break;
    }
    setcommand(Cont);
}

//--------------------------------------------------------------------------------------------
//Общие команды которые могут использоваться для anritsu и planar С4420

void Analayzer::Point(QString point){
     QString Point =":SENS:SWE:POIN "+point+"\n";
     setcommand(Point);
}

void Analayzer::Point(){
    QString Point = "SENS:SWEP:POIN?\n";
    setcommand(Point);
}

void Analayzer::Pow(QString power){
    QString Pow = ":SOUR:POW "+power+"\n";
    setcommand(Pow);
}

void Analayzer::SetFreqStart(QString freq){
    QString start = ":SENSe1:FREQuency:STARt " +freq+" \n";
    setcommand(start);
}

void Analayzer::SetFreqEnd(QString freq){
    QString stop =":SENSe1:FREQuency:STOP "+ freq+" \n";
    setcommand(stop);
}

void Analayzer::SetFreq(int range){
    SetFreqStart(freq[range*2]);
    SetFreqEnd(freq[range*2+1]);
}

void Analayzer::AverSWE(){
    QString AverSWE = ":SENSe:AVERage:SWEep?\n";
    setcommand(AverSWE);
}
void Analayzer::AverCLE(){
    QString AverCLE = ":SENSe:AVERage:CLEar\n";
    setcommand(AverCLE);
}
void Analayzer::AverCOUNT(){
    QString AverCOUNT = ":SENSe:AVERage:COUNt?\n";
    setcommand(AverCOUNT);
}

void Analayzer::SetAverCOUNT(QString point){
    QString AverCOUNT = ":SENSe:AVERage:COUNt "+point+"\n";
    setcommand(AverCOUNT);
}
void Analayzer::AverTYP(){
    QString AverTYP = ":SENSe:AVERage:TYP SWE\n";
     setcommand(AverTYP);
}
void Analayzer::AverON(){
    QString AverON = ":SENSe:AVERage ON\n";
     setcommand(AverON);
}
//--------------------------------------------------------------------------------------------

