#include "configuration.h"
#include "ui_configuration.h"

Configuration::Configuration(QWidget *parent):
    QDialog(parent),
    m_ui(new Ui::Configuration)
{
    m_ui->setupUi(this);

    connect(m_ui->applyButton, &QPushButton::clicked,
            this, &Configuration::apply);

    fillPortsParameters();
    updateSettings();
}

Configuration::Settings Configuration:: settings(uint8_t i ){
    switch(i) {
        case 0:
            return full;
              break;
        case 1:
            return first;
              break;
        case 2:
            return second;
              break;
        case 3:
            return tree;
              break;
        case 4:
            return four;
              break;
        default:
              break;
    }
}


Configuration::~Configuration()
{
    delete m_ui;
}

void Configuration::apply(){
    updateSettings();
    hide();
}

void Configuration::updateSettings(){
    //Полный диапазон
    full.att = list1.indexOf(this->m_ui->cmbAtt_full->currentText());

    full.pv = list2.indexOf(this->m_ui->cmbPs_full->currentText());

    full.pm618 = list3.indexOf(this->m_ui->cmbAtt2_full->currentText());

    full.dir = list4.indexOf(m_ui->cmbdir_full->currentText());

    //Первый диапазон
    first.att = list1.indexOf(this->m_ui->cmbAtt_first->currentText());

    first.pv = list2.indexOf(this->m_ui->cmbPs_first->currentText());

    first.pm618 = list3.indexOf(this->m_ui->cmbAtt2_first->currentText());

    first.dir = list4.indexOf(this->m_ui->cmbdir_first->currentText());


    //Второй диапазон
    second.att = list1.indexOf(this->m_ui->cmbAtt_second->currentText());

    second.pv = list2.indexOf(this->m_ui->cmbPs_second->currentText());

    second.pm618 = list3.indexOf(this->m_ui->cmbAtt2_second->currentText());

    second.dir = list4.indexOf(this->m_ui->cmbdir_second->currentText());


    //Третий диапазон
    tree.att = list1.indexOf(this->m_ui->cmbAtt_tree->currentText());

    tree.pv = list2.indexOf(this->m_ui->cmbPs_tree->currentText());

    tree.pm618 = list3.indexOf(this->m_ui->cmbAtt2_tree->currentText());

    tree.dir = list4.indexOf(this->m_ui->cmbdir_tree->currentText());


    //Четвертый диапазон
    four.att = list1.indexOf(this->m_ui->cmbAtt_four->currentText());

    four.pv = list2.indexOf(this->m_ui->cmbPs_four->currentText());

    four.pm618 = list3.indexOf(this->m_ui->cmbAtt2_four->currentText());

    four.dir = list4.indexOf(this->m_ui->cmbdir_four->currentText());
}


void Configuration::fillPortsParameters(){
    vector<int> d ={0, 5 ,11,22,45,90,180};
    troughalloptions(list2,d);
    vector<float> d1 ={0, 0.9 ,1.8,3.6,7.2,14.4};
    troughalloptions(list3,d1);

    for(int i =0; i < 32;i++){
        list1.append(QString::number(i));
        list1.append(QString::number(i+0.5));
    }

    m_ui->cmbAtt_full->addItems(list1);
    m_ui->cmbPs_full->addItems(list2);
    m_ui->cmbAtt2_full->addItems(list3);
    m_ui->cmbdir_full->addItems(list4);

    m_ui->cmbAtt_first->addItems(list1);
    m_ui->cmbPs_first->addItems(list2);
    m_ui->cmbAtt2_first->addItems(list3);
    m_ui->cmbdir_first->addItems(list4);

    m_ui->cmbAtt_second->addItems(list1);
    m_ui->cmbPs_second->addItems(list2);
    m_ui->cmbAtt2_second->addItems(list3);
    m_ui->cmbdir_second->addItems(list4);

    m_ui->cmbAtt_tree->addItems(list1);
    m_ui->cmbPs_tree->addItems(list2);
    m_ui->cmbAtt2_tree->addItems(list3);
    m_ui->cmbdir_tree->addItems(list4);

    m_ui->cmbAtt_four->addItems(list1);
    m_ui->cmbPs_four->addItems(list2);
    m_ui->cmbAtt2_four->addItems(list3);
    m_ui->cmbdir_four->addItems(list4);
}


bool comp(const long long& e1, const long long& e2) {
    return e1 > e2;
}

template <typename T>
void Configuration::troughalloptions(QStringList& list, vector<T> d){
    map<T, T> m;
    vector<pair<T, T>> v;
    sort(d.begin(), d.end(),comp);
    m[0] = 0;
    for (size_t i = 0; i < d.size(); i++) {
        for (auto j : m) {
            v.push_back({j.first+d[i],d[i]});
        }
        for (auto j : v) {
            if (m.count(j.first) == 0) {
                m[j.first] = j.second;
            }
        }
        v.clear();
    }
    for(auto x :m){
        list.append(QString::number(x.first));
    }
}
