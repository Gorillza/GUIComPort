#ifndef WAKE_H
#define WAKE_H

#include "MClib/include/common/types.h"
#include "MClib/include/common/buffer.h"
#include <MClib/include/common/wake_common.h>
#ifdef USE_PROGMEM
//#include <avr/pgmspace.h>
#endif

#ifndef WAKE_DATA_MAX_SIZE
#define WAKE_DATA_MAX_SIZE 54
#endif

extern uint8_t flag;
  
class CMCWake
{
    
private:
   
#ifndef USE_PROGMEM
    uint16_t m_CRC16Table[256];
#endif
    MCBuffer<WAKE_DATA_MAX_SIZE * 3 / 2> m_RX;
    MCBuffer<WAKE_DATA_MAX_SIZE + 10> m_tmp;

    /**
    * @brief Calculate CRC table
    */
    void  InitCRCTable();

    /**
     * @brief Encoding  byte sequence.
     * @param[in] src - pointer on input data
     * @param[in] src_size - input data size
     * @param[out] dst - pointer on output data size
     * @param[out] dst_size - output data size
     * @return 0 - success
     */
    void ByteStuffingEncodePackage(uint8_t* src, TBufferIndex src_size, uint8_t* dst, TBufferIndex* dst_size);

    /**
     * @brief Decoding  byte sequence.
     * @param[in] src - pointer on input data
     * @param[in] src_size - input data size
     * @param[out] dst - pointer on output data size
     * @param[out] dst_size - output data size
     * @return 0 - success
     */
    void ByteStuffingDecodePackage(uint8_t* src, TBufferIndex src_size);

    /**
    * @brief Return CRC for byte sequence.
    * @param[in] pData - pointer on data
    * @param[in] uiSize - data size
    * @return CRC
    */
    uint16_t GetCRC16(uint8_t* pData, TBufferIndex uiSize);


    /**
     * @brief Checking package correct.
     * @param[in] buff - pointer on package
     * @return 0 - success
     */
    uint8_t CheckPackage(uint8_t * pbuff);

    void ByteEncode(MCBaseBuffer* pFIFO, uint8_t data);

    void UpdateCRC16(uint16_t& crc, uint8_t data);

public:

    struct WakePackage {
        uint8_t nBoard;
        uint8_t nElement;
        uint8_t nCommand;
        uint16_t usSize;
        uint8_t data[WAKE_DATA_MAX_SIZE];
    };

    CMCWake();

    ~CMCWake();

    uint8_t Parse(uint8_t data,  WakePackage &package);

    void MakePackage(uint8_t nBoard, uint8_t nElement, uint8_t nCommand, MCBaseBuffer* pData, MCBaseBuffer* pOutFIFO);

    void MakePackage( WakePackage &pkg, MCBaseBuffer* pOutFIFO);

};
#endif // WAKE_H
