#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <string>
#include <vector>
#include <map>
using namespace std;

#include <QMainWindow>
#include <QSerialPort>
#include <QTcpSocket>
#include "configuration.h"
#include "bit_manipulation.h"
#include "connectors.h"
#include "analayzer.h"

#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitWrite(value, bit, bitvalue) (bitvalue ? bitSet(value, bit) : bitClear(value, bit))
#define bit(b) (1UL << (b))

void delay(int millisecondsToWait );

class QLabel;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class SettingsDialog;
class Analayzer;
class Configuration;
class Connectors;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QStringList list0 ={"Полный","Первый","Второй","Третий","Четветрый"};

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private://Функции для инициализации зависимостей/начальных значений
    void fillPortsParameters();
    void initActionsConnections();

private slots://Функции отображающие информацию и функцция для очистки
    void about();
    void clear();
    void showStatusMessage(const QString &message);
    void filltxtoutput(const QByteArray a);

    void buttonchanger(bool a);

private slots://Функция для отправки на плату команд
    void SendMassage(QByteArray d);

private slots://Все для работы тестирования
    void Range(uint8_t range,uint8_t att , uint8_t pv, uint8_t pm618, uint8_t dir , QString diapason);
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private slots://Функции для взаимодействия с микросхемой памяти
    void M95_read_data();
    void M95_write_data();

private slots://Вcе для работы с кастомной командой работает идеально не ирогать
    void SendCustomComand();
    void on_checkBox_stateChanged(int arg1);

    void on_actionConnect_triggered();
    void on_actionDisconnect_triggered();

    void on_actionConfigure_triggered();

    void on_actionAnritsu_triggered();

    void on_actionC4420_triggered();

signals:
    //Сигналы для взаиодействия с COM  портом
    void sgn_open_serialport();
    void sgn_close_serialport();
    void sgn_read_serialport();
    void sgn_write_serialport(QByteArray data);
    void sgn_show_settingdialog();

    //Сигналы для взаимодействия с анализатором
    void sgn_open_tcpsocket(int tf);
    void sgn_show_analayzer();
    void sgn_setcommand(QString command);
    void sgn_hold_analayzer();
    void sgn_cont_analayzer();
    void sgn_S12();
    void sgn_S21();
    void sgn_freq_range(int range_number);
    void sgn_memory_store(QString str);
public:
    QLabel *status = nullptr;
    Ui::MainWindow *ui;
    Configuration *m_configure = nullptr;
    Connectors *m_connector = nullptr;
private:
    Bit_Manipulation cusstom_command;
};
#endif // MAINWINDOW_H
