#include "MClib/include/protocols/wake.h"


#define WAKE_FEND ((uint8_t)0xC0)
#define WAKE_FESC ((uint8_t)0xDB)
#define WAKE_TFEND ((uint8_t)0xDC)
#define WAKE_TFESC ((uint8_t)0xDD)

/**
 * @brief  Wake package header
*/
// must be packed
typedef struct {
    uint8_t mark;        /*!< Begin package mark.*/
    uint8_t address_h;   /*!< Address, high part.*/
    uint8_t address_l;   /*!< Address, low part.*/
    uint8_t command;     /*!< Command.*/
    uint8_t data_size_h; /*!< Data size, high part.*/
    uint8_t data_size_l; /*!< Data size, low part.*/
} TWakeHeader, *PWakeHeader;


/** @brief  Wake package  */
// must be packed
typedef struct {
    TWakeHeader hdr;                  /*!< Wake package header.*/
    uint8_t data[WAKE_DATA_MAX_SIZE]; /*!< Data + CRC.*/
} TWakePackage, *PWakePackage;



#ifdef USE_PROGMEM
constexpr static uint16_t WakeCRC16Table[256] PROGMEM = {
        0x0000, 0x8005, 0x800f, 0x000a, 0x801b, 0x001e, 0x0014, 0x8011, 0x8033, 0x0036, 0x003c, 0x8039, 0x0028, 0x802d, 0x8027, 0x0022,
        0x8063, 0x0066, 0x006c, 0x8069, 0x0078, 0x807d, 0x8077, 0x0072, 0x0050, 0x8055, 0x805f, 0x005a, 0x804b, 0x004e, 0x0044, 0x8041,
        0x80c3, 0x00c6, 0x00cc, 0x80c9, 0x00d8, 0x80dd, 0x80d7, 0x00d2, 0x00f0, 0x80f5, 0x80ff, 0x00fa, 0x80eb, 0x00ee, 0x00e4, 0x80e1,
        0x00a0, 0x80a5, 0x80af, 0x00aa, 0x80bb, 0x00be, 0x00b4, 0x80b1, 0x8093, 0x0096, 0x009c, 0x8099, 0x0088, 0x808d, 0x8087, 0x0082, 
        0x8183, 0x0186, 0x018c, 0x8189, 0x0198, 0x819d, 0x8197, 0x0192, 0x01b0, 0x81b5, 0x81bf, 0x01ba, 0x81ab, 0x01ae, 0x01a4, 0x81a1, 
        0x01e0, 0x81e5, 0x81ef, 0x01ea, 0x81fb, 0x01fe, 0x01f4, 0x81f1, 0x81d3, 0x01d6, 0x01dc, 0x81d9, 0x01c8, 0x81cd, 0x81c7, 0x01c2, 
        0x0140, 0x8145, 0x814f, 0x014a, 0x815b, 0x015e, 0x0154, 0x8151, 0x8173, 0x0176, 0x017c, 0x8179, 0x0168, 0x816d, 0x8167, 0x0162, 
        0x8123, 0x0126, 0x012c, 0x8129, 0x0138, 0x813d, 0x8137, 0x0132, 0x0110, 0x8115, 0x811f, 0x011a, 0x810b, 0x010e, 0x0104, 0x8101, 
        0x8303, 0x0306, 0x030c, 0x8309, 0x0318, 0x831d, 0x8317, 0x0312, 0x0330, 0x8335, 0x833f, 0x033a, 0x832b, 0x032e, 0x0324, 0x8321, 
        0x0360, 0x8365, 0x836f, 0x036a, 0x837b, 0x037e, 0x0374, 0x8371, 0x8353, 0x0356, 0x035c, 0x8359, 0x0348, 0x834d, 0x8347, 0x0342, 
        0x03c0, 0x83c5, 0x83cf, 0x03ca, 0x83db, 0x03de, 0x03d4, 0x83d1, 0x83f3, 0x03f6, 0x03fc, 0x83f9, 0x03e8, 0x83ed, 0x83e7, 0x03e2, 
        0x83a3, 0x03a6, 0x03ac, 0x83a9, 0x03b8, 0x83bd, 0x83b7, 0x03b2, 0x0390, 0x8395, 0x839f, 0x039a, 0x838b, 0x038e, 0x0384, 0x8381, 
        0x0280, 0x8285, 0x828f, 0x028a, 0x829b, 0x029e, 0x0294, 0x8291, 0x82b3, 0x02b6, 0x02bc, 0x82b9, 0x02a8, 0x82ad, 0x82a7, 0x02a2, 
        0x82e3, 0x02e6, 0x02ec, 0x82e9, 0x02f8, 0x82fd, 0x82f7, 0x02f2, 0x02d0, 0x82d5, 0x82df, 0x02da, 0x82cb, 0x02ce, 0x02c4, 0x82c1, 
        0x8243, 0x0246, 0x024c, 0x8249, 0x0258, 0x825d, 0x8257, 0x0252, 0x0270, 0x8275, 0x827f, 0x027a, 0x826b, 0x026e, 0x0264, 0x8261, 
        0x0220, 0x8225, 0x822f, 0x022a, 0x823b, 0x023e, 0x0234, 0x8231, 0x8213, 0x0216, 0x021c, 0x8219, 0x0208, 0x820d, 0x8207, 0x0202
    };
#endif

CMCWake::CMCWake()
{
    InitCRCTable();
}

CMCWake::~CMCWake()
{

}

void CMCWake::InitCRCTable()
{
#ifndef USE_PROGMEM
    uint16_t r;
    uint16_t i;
    uint8_t j;
    for(i = 0; i < 256; i++) {
        r = i << 8;
        for(j = 0; j < 8; j++) {
            if(r & (1 << 15))
                r = (r << 1) ^ 0x8005;
            else
                r = r << 1;
        }
        m_CRC16Table[i] = r;
    }
#endif
}


void CMCWake::ByteStuffingEncodePackage(uint8_t* src, TBufferIndex src_size, uint8_t* dst, TBufferIndex* dst_size)
{
    TBufferIndex i;
    *dst_size = 0;
    if(src_size > 0) {
        dst[*dst_size] = src[0];
        (*dst_size)++;
        for(i = 1; i < src_size; i++) {
            if(src[i] == WAKE_FEND) {
                dst[*dst_size] = WAKE_FESC;
                (*dst_size)++;
                dst[*dst_size] = WAKE_TFEND;
            } else if(src[i] == WAKE_FESC) {
                dst[*dst_size] = WAKE_FESC;
                (*dst_size)++;
                dst[*dst_size] = WAKE_TFESC;
            } else {
                dst[*dst_size] = src[i];
            }
            (*dst_size)++;
        }
    }
}

void CMCWake::ByteStuffingDecodePackage(uint8_t* src, TBufferIndex src_size)
{
    TBufferIndex i;
    if(src_size > 0) {
        m_tmp.Push(src[0]);
        for(i = 1; i < src_size &&  i < m_tmp.Capacity(); i++) {
            if(src[i] == WAKE_FESC) {
                if(src[i + 1] == WAKE_TFEND) {
                    m_tmp.Push(WAKE_FEND);
                    i++;
                } else if(src[i + 1] == WAKE_TFESC) {
                    m_tmp.Push(WAKE_FESC);
                    i++;
                }
            } else {
                m_tmp.Push(src[i]);
            }
        }
    }
}

uint16_t CMCWake::GetCRC16(uint8_t* pData, TBufferIndex uiSize)
{
    volatile uint16_t crc;

    crc = 0xFFFF;
#ifdef USE_PROGMEM
    uint16_t tmp;
#endif
    while(uiSize--) {
#ifdef USE_PROGMEM
        tmp = pgm_read_word(&(WakeCRC16Table[((crc >> 8) ^ *pData++) & 0xFF]));
        crc = tmp ^ (crc << 8);
#else

        crc = m_CRC16Table[((crc >> 8) ^ *pData++) & 0xFF] ^ (crc << 8);
#endif
    }
    crc ^= 0xFFFF;


    //RS485_Transmit((uint8_t*)crc, 2, &RS485_USART1);


    return crc;
}

uint8_t CMCWake::CheckPackage(  uint8_t * pbuff)
{
    PWakePackage buff = (PWakePackage)pbuff;
    volatile uint16_t size;
    volatile uint16_t crc = 0;
    volatile uint8_t result = 0xE1;
    if(buff->hdr.mark == WAKE_FEND) {
        result = 0xE2;
        if(BIT_CHECK(buff->hdr.address_h, 7)) {
            result = 0xE3;
            if(!BIT_CHECK(buff->hdr.command, 7)) {
                result = 0xE4;
                if(!BIT_CHECK(buff->hdr.data_size_h, 7)) {
                    result = 0xE5;
                    size = (buff->hdr.data_size_h << 8) | buff->hdr.data_size_l;
                    crc = GetCRC16((uint8_t*)&(buff->hdr.address_h), size + sizeof(TWakeHeader) - 1);
                    if((((uint8_t)(crc >> 8)) == (uint8_t)buff->data[size]) &&
                       (((uint8_t)(crc)) == buff->data[size + 1]))
                        result = 0;
                }
            }
        }
    }
    return result;
}


uint8_t CMCWake::Parse(uint8_t data, WakePackage &package)
{
    m_RX.Push(data);

    TBufferIndex last_processed = 0;
    uint8_t result = 0xE0;
    TBufferIndex size = m_RX.Size();
    TBufferIndex cnt = size;
    uint8_t *p = m_RX.Data();
    PWakeHeader phdr;
    PWakePackage ppackage;
    memset((void *) &package, 0, sizeof(package));
    const TBufferIndex min_size = (sizeof(TWakeHeader) + 4);
    if((TBufferIndex)size >= (TBufferIndex)min_size) {
        while(cnt && result != 0) {
            if((*p) == WAKE_FEND) {
                m_tmp.HardClear();
                ByteStuffingDecodePackage(p, cnt);
                result = CheckPackage(m_tmp.Data());
                if(result == 0) {
                    phdr = (PWakeHeader)m_tmp.Data();
                    ppackage = (PWakePackage)phdr;
                    cnt = size - cnt;
                    size = (TBufferIndex)( phdr->data_size_h << 8 | phdr->data_size_l);
                    package.nBoard = BIT_CLEAR(phdr->address_h, 7);
                    package.nElement = phdr->address_l;
                    package.nCommand = phdr->command;
                    package.usSize = size;
                    phdr++;
                    for(TBufferIndex i =0; i< size; i++)
                        package.data[i] = ppackage->data[i];

                    last_processed = cnt + size + min_size;
                }
            }
            cnt--;
            p++;
        }
        m_RX.Erase(last_processed);
        if(m_RX.Size() == m_RX.Capacity())
            m_RX.HardClear();
    }
    return result;
}



inline void CMCWake::ByteEncode(MCBaseBuffer* pOutFIFO, uint8_t data)
{
    if(data == WAKE_FEND) {
        pOutFIFO->FifoWrite(WAKE_FESC);
        pOutFIFO->FifoWrite(WAKE_TFEND);
    } else if(data == WAKE_FESC) {
        pOutFIFO->FifoWrite( WAKE_FESC);
        pOutFIFO->FifoWrite( WAKE_TFESC);
    } else
        pOutFIFO->FifoWrite( data);
}

inline void CMCWake::UpdateCRC16(uint16_t& crc, uint8_t data)
{
#ifdef USE_PROGMEM
    uint16_t tmp;
    tmp = pgm_read_word(&(WakeCRC16Table[((crc >> 8) ^ data) & 0xFF]));
    crc = tmp ^ (crc << 8);
#else
    crc = m_CRC16Table[((crc >> 8) ^ data) & 0xFF] ^ (crc << 8);
#endif

}



void CMCWake::MakePackage(uint8_t nBoard, uint8_t nElement, uint8_t nCommand, MCBaseBuffer* pData, MCBaseBuffer* pOutFIFO)
{
    TBufferIndex i;
    uint16_t crc = 0xFFFF;

    nBoard |= 0x80;

    // mark
    pOutFIFO->FifoWrite(WAKE_FEND);

    // address
    ByteEncode(pOutFIFO, nBoard);
    UpdateCRC16(crc, nBoard);

    ByteEncode(pOutFIFO, nElement);
    UpdateCRC16(crc, nElement);

    // command
    ByteEncode(pOutFIFO, nCommand);
    UpdateCRC16(crc, nCommand);

    // size
    ByteEncode(pOutFIFO, (pData->Size() >> 8) & 0x7F);
    UpdateCRC16(crc, (pData->Size() >> 8) & 0x7F);

    ByteEncode(pOutFIFO, (uint8_t)pData->Size());
    UpdateCRC16(crc, (uint8_t)pData->Size());

    // data
    TBufferIndex  n = pData->Size();
    uint8_t *p =pData->Data();
    while(n--) {
        ByteEncode(pOutFIFO, *p);
        UpdateCRC16(crc, *p);
        p++;
    }

    //crc
    crc ^= 0xFFFF;
    ByteEncode(pOutFIFO, (uint8_t)(crc >> 8));
    ByteEncode(pOutFIFO, (uint8_t)crc);
}



void CMCWake::MakePackage(WakePackage &pkg, MCBaseBuffer* pOutFIFO)
{
    TBufferIndex i;
    uint16_t crc = 0xFFFF;

    pkg.nBoard |= 0x80;

    // mark
    pOutFIFO->FifoWrite(WAKE_FEND);

    // address
    ByteEncode(pOutFIFO, pkg.nBoard);
    UpdateCRC16(crc, pkg.nBoard);

    ByteEncode(pOutFIFO, pkg.nElement);
    UpdateCRC16(crc, pkg.nElement);

    // command
    ByteEncode(pOutFIFO, pkg.nCommand);
    UpdateCRC16(crc, pkg.nCommand);

    // size
    ByteEncode(pOutFIFO, (pkg.usSize >> 8) & 0x7F);
    UpdateCRC16(crc, (pkg.usSize >> 8) & 0x7F);

    ByteEncode(pOutFIFO, (uint8_t)pkg.usSize);
    UpdateCRC16(crc, (uint8_t)pkg.usSize);

    // data
    uint8_t n = pkg.usSize;

    for(uint8_t i =0; i< n; i++) {
        ByteEncode(pOutFIFO, pkg.data[i]);
        UpdateCRC16(crc, pkg.data[i]);
    }

    //crc
    crc ^= 0xFFFF;
    ByteEncode(pOutFIFO, (uint8_t)(crc >> 8));
    ByteEncode(pOutFIFO, (uint8_t)crc);
}
