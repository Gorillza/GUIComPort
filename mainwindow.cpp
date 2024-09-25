#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QtSerialPort/QSerialPort>

#include "bit_manipulation.h"
#include <algorithm>
#include "settingsdialog.h"
#include "analayzer.h"
#include <string>
#include<iostream>
#include<array>
using namespace std;



uint8_t flag =0;

//------------------------------------------------------------------------------------------------------------------------
//конструктор
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_configure(new Configuration)
    , status(new QLabel)
    , m_connector(new Connectors)
{

    ui->setupUi(this);

    ui->txtOutput->setReadOnly(true);


    ui->statusbar->addWidget(status);

    initActionsConnections();

    fillPortsParameters();

//    ui->sendcmd->setEnabled(false);
//    ui->pushButton->setEnabled(false);
//    ui->pushButton_2->setEnabled(false);
//    ui->M95_read->setEnabled(false);
//    ui->M95_write->setEnabled(false);
    ui->txtOutput->append("готов к работе");
}


//Деструктор
MainWindow::~MainWindow()
{
    delete ui;
}

//------------------------------------------------------------------------------------------------------------------------
//Инициализация взаимосвязи слотов и тригеров
void MainWindow::initActionsConnections()
{
    //Для работы меню
    connect(ui->actionQuit, &QAction::triggered, this, &MainWindow::close);
    connect(ui->actionAbout, &QAction::triggered, this, &MainWindow::about);
    connect(ui->action_test, &QAction::triggered, m_configure, &Configuration::show);
    connect(ui->actionClear, &QAction::triggered, this, &MainWindow::clear);
    connect(ui->action_2,&QAction::triggered, m_connector, &Connectors::show);

    //Для обработки нажатия кнопок
    connect(ui->sendcmd,&QPushButton::clicked,this,&MainWindow::SendCustomComand);

    //Для работы с памятью
    connect(ui->M95_read,&QPushButton::clicked,this,&MainWindow::M95_read_data);
    connect(ui->M95_write,&QPushButton::clicked,this,&MainWindow::M95_write_data);
}

//Заполнение данных в кнопки
void MainWindow::fillPortsParameters()
{
    ui->cmbRange->addItems(list0);
    ui->cmbAtt->addItems(m_configure->list1);
    ui->cmbPs->addItems(m_configure->list2);
    ui->cmbAtt2->addItems(m_configure->list3);
    ui->cmbdir->addItems(m_configure->list4);
}

//------------------------------------------------------------------------------------------------------------------------
//Функции отображающие информацию и функцция для очистки
void MainWindow::about()
{
    QMessageBox::about(this, tr("About Simple Terminal"),
                       tr("The <b>Simple Terminal</b> example demonstrates how to "
                          "use the Qt Serial Port module in modern GUI applications "
                          "using Qt, with a menu bar, toolbars, and a status bar."));
}

void MainWindow::clear(){
    ui->txtOutput->clear();
}

void MainWindow::showStatusMessage(const QString &message)
{
    status->setText(message);
}
//------------------------------------------------------------------------------------------------------------------------
void MainWindow::filltxtoutput(const QByteArray data){
    ui->txtOutput->append("Мы приняли:");
    ui->txtOutput->append(data.toHex()+"\n");
}


void MainWindow:: buttonchanger(bool a){
    ui->actionConnect->setEnabled(a);
    ui->actionDisconnect->setEnabled(!a);
    ui->actionConfigure->setEnabled(a);
    ui->sendcmd->setEnabled(!a);
    ui->pushButton->setEnabled(!a);
    ui->pushButton_2->setEnabled(!a);
    ui->M95_read->setEnabled(!a);
    ui->M95_write->setEnabled(!a);
}

//------------------------------------------------------------------------------------------------------------------------
//Функция для отправки на плату команд
void MainWindow::SendMassage(QByteArray d){
    ui->txtOutput->append("Мы отправили:");
    ui->txtOutput->append(d.toHex());
    emit sgn_write_serialport(d);
//    m_settings->serialport->write(d);
//    m_settings->serialport->waitForBytesWritten();
//    ui->txtOutput->append(d.toHex());
    //emit sgn_read_serialport();
    //readData();
}
//------------------------------------------------------------------------------------------------------------------------
//Все для работы тестирования
void MainWindow::Range(uint8_t range,uint8_t att , uint8_t pv, uint8_t pm618, uint8_t dir , QString diapason){

    vector<uint8_t> pdata(4,0);
    Bit_Manipulation BM(pdata);
    BM.MakePdata(range, att, pv, pm618,dir);

    //Выключили анритсу
    emit sgn_hold_analayzer();

    //Выключили усилитель
    BM.SetKmodDisable();
    ui->txtOutput->append("Выключили усилитель");
    SendMassage(BM.Getdata());
    delay(10);

    //Включили усилитель
    BM.SetKmodEnable();
    ui->txtOutput->append("Включили усилитель");
    SendMassage(BM.Getdata());
    delay(10);

    //Включили анритсу

    emit sgn_cont_analayzer();
    delay(2000);

    if(att > 4){
        att-=4;
        BM.SetAtt(att);
    }else{
        att = 0;
        BM.SetAtt(att);
    }


    if(pv > 4){
        pv-=4;
        BM.SetPhase(pv);
    }else{
        pv = 64-(4-pv);
        BM.SetPhase(pv);
    }

    for(uint8_t i =0; i <9;i++){
        for(uint8_t j = 0; j<9;j++){
            if(BM.GetPhase()==63){
                BM.SetPhase(0);
            }else{
                BM.SetPhase(BM.GetPhase()+1);
            }
            //Направили на плату команду
            ui->txtOutput->append("АТТ ФПЛ: "+ m_configure->list1[BM.GetAtt()]+ "ФВ ФПЛ"+m_configure->list2[BM.GetPhase()]);
            SendMassage(BM.Getdata());
            delay(700);
            //Сохранили в папку в формате CSV
            emit sgn_setcommand(":MMEMory:STORe 'C:/pro/"+diapason+"_k"+QString::number(bitRead(BM.Getpdata()[3],0))+"_att" +m_configure->list1[BM.GetAtt()]+"pv"+m_configure->list2[BM.GetPhase()]+ ".csv' \n");
            //m_analayzer->setcommand(":MMEMory:STORe 'C:/pro/"+diapason+"_k"+QString::number(bitRead(BM.Getpdata()[3],0))+"_att" +m_configure->list1[BM.GetAtt()]+"pv"+m_configure->list2[BM.GetPhase()]+ ".csv' \n");

            delay(2000);
            ui->txtOutput->append("'C:/pro/"+diapason+"_k"+QString::number(bitRead(BM.Getpdata()[3],0))+"_att" +m_configure->list1[BM.GetAtt()]+"pv"+m_configure->list2[BM.GetPhase()]+ ".csv'\n");

            while(flag){
                delay(500);
                if(!flag){
                    break;
                }
            }
        }
        BM.SetAtt(BM.GetAtt()+1);
        BM.SetPhase(pv);
    }
    emit sgn_hold_analayzer();

    BM.SetKmodDisable();
    SendMassage(BM.Getdata());
    delay(10);
}

//кнопка старта тестирования
void MainWindow::on_pushButton_clicked(){
    Configuration::Settings p;

    int k =0;
    for (int i =0;i < 5;i++) {
        p = m_configure->settings(i);
        //Полный диапазон
        ui->txtOutput->append(list0[i]+"\nАТТ ФПЛ: "+m_configure->list1[p.att]+
                                              " ФВ ФПЛ: " +m_configure->list2[p.pv]+
                                         " АТТ УС: " +m_configure->list3[p.pm618]+
                                            " Напр:" + m_configure->list4[p.dir]);

        emit sgn_freq_range(i);

        emit sgn_S21();
        Range(i,p.att,p.pv,p.pm618,1,list0[i]);

        emit sgn_S12();
        Range(i,p.att,p.pv,p.pm618,0,list0[i]);

        k+=2;
    }
}


//кнопка стопа
void MainWindow::on_pushButton_2_clicked(){
     if(flag){
         flag =0;
         ui->txtOutput->append("Программа возобновлена");
     }else{
         flag = 1;
         ui->txtOutput->append("Программа приостоновлена");
     }

}
//------------------------------------------------------------------------------------------------------------------------
//Все для работы с памятью
void MainWindow::M95_write_data(){
    //Создали массив для записи в память
    //менять только это для записи в память
    vector<uint8_t> pdata = {0x1C, 0x00,
                             0x00, 0x00,
                             0x00, 0x00,
                             0x00, 0x00
                             //итд для одной частоты два значения тк у нас отведено 16 бит на одно значение частоты
                            };

    //Создали экземпляр класса записав туда данные с масиива pdata
    Bit_Manipulation BM(pdata);

    //переформатировали для нужного вида команду чтобы отправить с управляющей командой
    BM.reformat(0x80,0x01,0x01);

    //вывод на экран данных для понимания происходящего
    ui->txtOutput->append("Мы отправили:");
    ui->txtOutput->append(BM.Getdata().toHex());

    //Отправка по COM  порту
    emit sgn_write_serialport(BM.Getdata());

    //Чтение команды отправляемой с платы обратно нам должна совпасть с той что направили
    emit sgn_read_serialport();
}


void MainWindow::M95_read_data(){
    vector<uint8_t> pdata = {0,10};
    Bit_Manipulation BM(pdata);
    BM.reformat(0x80,0x00,0x55);
    ui->txtOutput->append("Мы отправили:");
    ui->txtOutput->append(BM.Getdata().toHex());

    emit sgn_write_serialport(BM.Getdata());
    emit sgn_read_serialport();
}

//-------------------------------------------------------------------------------------------------------------------------
//Вcе для работы с кастомной командой работает идеально не ирогать
void MainWindow::SendCustomComand(){

    uint8_t range = list0.indexOf(this->ui->cmbRange->currentText());

    uint8_t att = m_configure->list1.indexOf(this->ui->cmbAtt->currentText());

    uint8_t pv = m_configure->list2.indexOf(this->ui->cmbPs->currentText());

    uint8_t pm618 = m_configure->list3.indexOf(this->ui->cmbAtt2->currentText());

    uint8_t dir = m_configure->list4.indexOf(this->ui->cmbdir->currentText());

    cusstom_command.MakePdata(range,att,pv,pm618,dir);

    ui->txtOutput->append("АТТ ФПЛ:"+m_configure->list1[cusstom_command.GetAtt()]+" ФВ ФПЛ: " +m_configure->list2[cusstom_command.GetPhase()]+" АТТ УС: " +m_configure->list3[cusstom_command.GetPM618()]+" Напр:" + m_configure->list4[cusstom_command.GetDir()]);

    emit sgn_freq_range((int)range);

    SendMassage(cusstom_command.Getdata());

    //Для вкладки с разьемами чтобы при отправке обнавляллись цвета (красный/зеленый)
    m_connector->ChangeData(cusstom_command.Getpdata());
}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
    if(arg1 == 2){
        cusstom_command.SetKmodEnable();
    }else{
        cusstom_command.SetKmodDisable();
    }
}


void MainWindow::on_actionConnect_triggered()
{
    emit sgn_open_serialport();
}

void MainWindow::on_actionDisconnect_triggered()
{
    emit sgn_close_serialport();
}

void MainWindow::on_actionConfigure_triggered()
{
    emit sgn_show_settingdialog();
}

void MainWindow::on_actionAnritsu_triggered()
{
    emit sgn_open_tcpsocket(0);
    emit sgn_show_analayzer();
}

void MainWindow::on_actionC4420_triggered()
{
    emit sgn_open_tcpsocket(1);
    emit sgn_show_analayzer();
}
