#ifndef BIT_MANIPULATION_H
#define BIT_MANIPULATION_H

#include <QPlainTextEdit>
#include <vector>
#include <QString>
#include "MClib/include/protocols/wake.h"
#include "MClib/include/common/types.h"
#include "MClib/include/common/buffer.h"
#include <QByteArray>

using namespace std;

typedef MCBuffer<64> IOBuffer;

class Bit_Manipulation
{
public:
    Bit_Manipulation(vector<uint8_t>& data_);

    Bit_Manipulation();

    vector<uint8_t> Getpdata();

    QByteArray Getdata();

    void reformat(uint8_t nBoard, uint8_t nElement, uint8_t nCommand);

    void SetKmodEnable();

    void SetKmodDisable();

    void SetDir(uint8_t dir);

    bool GetKmod();

    void SetDirEnable();

    void SetDirDisable();

    void TogleDir();

    bool GetDir();

    uint8_t GetAtt();

    uint8_t GetPhase();

    uint8_t GetRange();

    void SetAtt(uint8_t data);

    void SetPhase(uint8_t data);

    void SetRange(uint8_t range);

    void CleareRange();

    uint8_t GetPM618();

    void SetPM618(uint8_t pm618);

    void SendMassage();

    void MakePdata(uint8_t range_,uint8_t att_, uint8_t pv_, uint8_t pm618_, uint8_t k);

private:
    vector<uint8_t> pdata;
    QByteArray data;
    uint8_t att;
    uint8_t pv;
    uint8_t pm618;
    uint8_t dir;

    IOBuffer SetBuf;
    IOBuffer GetBuf;
};



#endif // BIT_MANIPULATION_H
