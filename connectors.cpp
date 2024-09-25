#include "connectors.h"
#include "ui_connectors.h"

#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitWrite(value, bit, bitvalue) (bitvalue ? bitSet(value, bit) : bitClear(value, bit))
#define bit(b) (1UL << (b))

Connectors::Connectors(QWidget *parent):
    QDialog(parent),
    m_ui(new Ui::Connectors)
{
    m_ui->setupUi(this);

    connect(m_ui->applyButton, &QPushButton::clicked,
            this, &Connectors::apply);

    pdata.resize(4,0);
}

Connectors::~Connectors()
{
    delete m_ui;
}

void Connectors::apply(){
    hide();
}

void Connectors::ChangeData(vector<uint8_t> a){
    pdata = a;
    UpdateBG();
}


void Connectors::UpdateBG(){
    //--------------------------------------------------
    //k
    if(bitRead(pdata[3],0)){
        SetGreen(m_ui->K);
        SetGreen(m_ui->KK);
    }else{
        SetRed(m_ui->K);
        SetRed(m_ui->KK);
    }

    //--------------------------------------------------
    //PM618
    if(bitRead(pdata[3],1)){
        SetGreen(m_ui->PM0);
    }else{
        SetRed(m_ui->PM0);
    }

    if(bitRead(pdata[3],2)){
        SetGreen(m_ui->PM1);
    }else{
        SetRed(m_ui->PM1);
    }

    if(bitRead(pdata[3],3)){
        SetGreen(m_ui->PM2);
    }else{
        SetRed(m_ui->PM2);
    }

    if(bitRead(pdata[3],4)){
        SetGreen(m_ui->PM3);
    }else{
        SetRed(m_ui->PM3);
    }

    if(bitRead(pdata[3],5)){
        SetGreen(m_ui->PM4);
    }else{
        SetRed(m_ui->PM4);
    }

    if(bitRead(pdata[3],6)){
        SetGreen(m_ui->PM5);
    }else{
        SetRed(m_ui->PM5);
    }
    //--------------------------------------------------
    //Filtr
    if(bitRead(pdata[3],7)){
        SetGreen(m_ui->F0);
    }else{
        SetRed(m_ui->F0);
    }

    if(bitRead(pdata[2],0)){
        SetGreen(m_ui->F1);
    }else{
        SetRed(m_ui->F1);
    }

    if(bitRead(pdata[2],1)){
        SetGreen(m_ui->F2);
    }else{
        SetRed(m_ui->F2);
    }

    if(bitRead(pdata[2],2)){
        SetGreen(m_ui->F3);
    }else{
        SetRed(m_ui->F3);
    }

    if(bitRead(pdata[2],3)){
        SetGreen(m_ui->F4);
    }else{
        SetRed(m_ui->F4);
    }

    if(bitRead(pdata[2],4)){
        SetGreen(m_ui->F5);
    }else{
        SetRed(m_ui->F5);
    }

    if(bitRead(pdata[2],5)){
        SetGreen(m_ui->F6);
    }else{
        SetRed(m_ui->F6);
    }
    //--------------------------------------------------
    //Фазавращатель
    if(bitRead(pdata[2],6)){
        SetGreen(m_ui->FV0);
    }else{
        SetRed(m_ui->FV0);
    }

    if(bitRead(pdata[2],7)){
        SetGreen(m_ui->FV1);
    }else{
        SetRed(m_ui->FV1);
    }

    if(bitRead(pdata[1],0)){
        SetGreen(m_ui->FV2);
    }else{
        SetRed(m_ui->FV2);
    }

    if(bitRead(pdata[1],1)){
        SetGreen(m_ui->FV3);
    }else{
        SetRed(m_ui->FV3);
    }

    if(bitRead(pdata[1],2)){
        SetGreen(m_ui->FV4);
    }else{
        SetRed(m_ui->FV4);
    }

    if(bitRead(pdata[1],3)){
        SetGreen(m_ui->FV5);
    }else{
        SetRed(m_ui->FV5);
    }
    //--------------------------------------------------

    if(bitRead(pdata[1],4)){
        SetGreen(m_ui->AT0);
    }else{
        SetRed(m_ui->AT0);
    }

    if(bitRead(pdata[1],5)){
        SetGreen(m_ui->AT1);
    }else{
        SetRed(m_ui->AT1);
    }

    if(bitRead(pdata[1],6)){
        SetGreen(m_ui->AT2);
    }else{
        SetRed(m_ui->AT2);
    }

    if(bitRead(pdata[1],7)){
        SetGreen(m_ui->AT3);
    }else{
        SetRed(m_ui->AT3);
    }

    if(bitRead(pdata[0],0)){
        SetGreen(m_ui->AT4);
    }else{
        SetRed(m_ui->AT4);
    }

    if(bitRead(pdata[0],1)){
        SetGreen(m_ui->AT5);
    }else{
        SetRed(m_ui->AT5);
    }
    //--------------------------------------------------
    if(bitRead(pdata[0],2)){
        SetGreen(m_ui->K_dop);
    }else{
        SetRed(m_ui->K_dop);
    }


}

void Connectors::SetRed(QLabel* a){
    a->setStyleSheet("QLabel { background-color: red; }");
}


void Connectors::SetGreen(QLabel* a){
    a->setStyleSheet("QLabel { background-color: green; }");
}
