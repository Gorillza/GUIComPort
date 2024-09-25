#ifndef CONNECTORS_H
#define CONNECTORS_H

#include <QDialog>
#include <vector>
#include <QLabel>
using namespace std;

QT_BEGIN_NAMESPACE

namespace Ui {
class Connectors;
}

QT_END_NAMESPACE

class Connectors : public QDialog
{
    Q_OBJECT

public:
    explicit Connectors(QWidget *parent = nullptr);
    ~Connectors();

    void SetRed(QLabel* a);

    void SetGreen(QLabel* a);

    void apply();

    void ChangeData(vector<uint8_t> a);

    void UpdateBG();

private:
    Ui::Connectors *m_ui = nullptr;
    vector<uint8_t> pdata;
};



#endif // CONNECTORS_H
