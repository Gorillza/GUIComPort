#include "bit_manipulation.h"

#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitWrite(value, bit, bitvalue) (bitvalue ? bitSet(value, bit) : bitClear(value, bit))
#define bit(b) (1UL << (b))

Bit_Manipulation::Bit_Manipulation(vector<uint8_t>& data_)
    :pdata(data_)
{

}

Bit_Manipulation::Bit_Manipulation(){
    pdata.resize(4,0);
}

vector<uint8_t> Bit_Manipulation::Getpdata(){
    return pdata;
}

QByteArray Bit_Manipulation::Getdata(){
    this->reformat(0x80, 0x00,0x01);
    return data;
}

void Bit_Manipulation::reformat(uint8_t nBoard, uint8_t nElement, uint8_t nCommand){
    SetBuf.HardClear();
    GetBuf.HardClear();

    for (size_t i =0;i < pdata.size();i++) {
         SetBuf.Push(pdata[i]);
    }

    CMCWake wparser1;

    wparser1.MakePackage(nBoard,nElement,nCommand,&SetBuf,&GetBuf);

    data.resize(GetBuf.Size());
    for(int i = 0;  i< data.size(); i++){
        uint8_t t =0;
         GetBuf.FifoRead(t);
         data[i] = t;
    }
    //ui->txtOutput->append(data1.toHex());
}


void Bit_Manipulation::SetKmodEnable(){
    bitSet(pdata[3],6);
}

void Bit_Manipulation::SetKmodDisable(){
    bitClear(pdata[3],6);
}

void Bit_Manipulation::SetDir(uint8_t dir){
    if(dir == 1){
        bitSet(pdata[3],0);
    }else{
        bitClear(pdata[3],0);
    }
}

void Bit_Manipulation::SetDirEnable(){
    bitSet(pdata[3],0);
}

void Bit_Manipulation::SetDirDisable(){
    bitClear(pdata[3],0);
}

void Bit_Manipulation::TogleDir(){
    if(bitRead(pdata[3],0) == 1){
        bitClear(pdata[3],0);
    }else{
        bitSet(pdata[3],0);
    }
}

bool Bit_Manipulation::GetKmod(){
    return bitRead(pdata[3],6);
}

bool Bit_Manipulation::GetDir(){
    return bitRead(pdata[3],0);
}

uint8_t Bit_Manipulation::GetAtt(){
    uint8_t att_mack = 0x3F;

    for(int i =0; i <6;i++){
        if(i<=3){
            if(bitRead(pdata[1],i+4)!=0){
                bitClear(att_mack,i);
            }
        }else{
            if(bitRead(pdata[0],i-4)!=0){
                bitClear(att_mack,i);
            }
        }
    }
    return att_mack;
}

uint8_t Bit_Manipulation::GetPhase(){
    uint8_t phase_mack = 0x3F;

    for(int i =0; i <6;i++){
        if(i<2){
            if(bitRead(pdata[2],i+6)!=0){
                bitClear(phase_mack,i);
            }
        }else{
            if(bitRead(pdata[1],i-2)!=0){
                bitClear(phase_mack,i);
            }
        }
    }
    return phase_mack;
}


void Bit_Manipulation::SetAtt(uint8_t data){

    for(int i =0; i < 6;i++){
        if(bitRead(data,i)==0){
            if(i <=3){
                bitSet(pdata[1],4+i);
            }else{
                bitSet(pdata[0],i-4);
            }
        }else{
            if(i <=3){
                bitClear(pdata[1],4+i);
            }else{
                bitClear(pdata[0],i-4);
            }
        }
    }
}

void Bit_Manipulation::SetPhase(uint8_t data){

    for(int i =0; i <6;i++){
        if(bitRead(data,i)==0){
            if(i<2){
                bitSet(pdata[2],i+6);
            }else{
                bitSet(pdata[1],i-2);
            }
        }else{
            if(i<2){
                bitClear(pdata[2],i+6);
            }else{
                bitClear(pdata[1],i-2);
            }
        }
    }
}


void Bit_Manipulation::SetRange(uint8_t range){
    CleareRange();
    bitSet(pdata[2],5);
    for(int i =0; i <6;i++){
        if(bitRead(range,i)!=0){
            if(i == 0){
                bitSet(pdata[3],7);
            }else{
                bitSet(pdata[2],i-1);
            }
        }
    }
}

void Bit_Manipulation::CleareRange(){
    for(int i =0; i <6;i++){
        if(i==0){
            bitClear(pdata[3],7);
        }else{
            bitClear(pdata[2],i-1);
        }
    }
}

uint8_t Bit_Manipulation::GetRange(){
    uint8_t range_mack = 0;

    for(int i =0; i <6;i++){
        if(i<1){
            if(bitRead(pdata[3],i+7)!=0){
                bitSet(range_mack,i);
            }
        }else{
            if(bitRead(pdata[2],i-1)!=0){
                bitSet(range_mack,i);
            }
        }
    }
    return range_mack;
}


void Bit_Manipulation::SetPM618(uint8_t pm618){
    for(int i =0; i < 5; i++){
        if(bitRead(pm618,i)!=0){
            bitSet(pdata[3],i+1);
        }else{
            bitClear(pdata[3],i+1);
        }
    }
}

uint8_t Bit_Manipulation::GetPM618(){
    uint8_t PM618_mack = 0;

    for(int i =0; i <5 ;i++){
        if(bitRead(pdata[3],i+1)!=0){
            bitSet(PM618_mack,i);
        }
    }
    return PM618_mack;
}

void Bit_Manipulation::MakePdata(uint8_t range_,uint8_t att_, uint8_t pv_, uint8_t pm618_, uint8_t k){
    pdata[0] = 0x38;

    SetRange(range_);
    SetAtt(att_);
    SetPhase(pv_);
    SetPM618(pm618_);
    SetDir(k);
}
