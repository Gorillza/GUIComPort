#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QDialog>
#include "bit_manipulation.h"
#include <QStringList>
#include <vector>
#include <map>
using namespace std;


QT_BEGIN_NAMESPACE

namespace Ui {
class Configuration;
}

class QIntValidator;

QT_END_NAMESPACE


class Configuration : public QDialog
{
      Q_OBJECT

public:
    QStringList list1 ={};
    QStringList list2 ={};
    QStringList list3 ={};
    QStringList list4 ={"Обратное","Прямое"};

    struct Settings {
        uint8_t att;
        uint8_t pv;
        uint8_t pm618;
        uint8_t dir;
    };

    Settings full;
    Settings first;
    Settings second;
    Settings tree;
    Settings four;

    explicit Configuration(QWidget *parent = nullptr);
    ~Configuration();

    Settings settings(uint8_t);

private slots:
    void apply();

public:
    template <typename T>
    void troughalloptions(QStringList& list, vector<T> d);
    void fillPortsParameters();
    void updateSettings();
private:
    Ui::Configuration *m_ui = nullptr;
};

#endif // CONFIGURATION_H
