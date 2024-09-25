#ifndef MY_TYPES_H_
#define MY_TYPES_H_

#include <MClib/include/common/buffer.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>



#define DATA_REGISTER_EMPTY (1<<UDRE0)
#define RX_COMPLETE (1<<RXC0)
#define FRAMING_ERROR (1<<FE0)
#define PARITY_ERROR (1<<UPE0)
#define DATA_OVERRUN (1<<DOR0)

#define BIT_SET(a, b) ((a) |= (1 << (b)))
#define BIT_CLEAR(a, b) ((a) &= ~(1 << (b)))
#define BIT_FLIP(a, b) ((a) ^= (1 << (b)))
#define BIT_CHECK(a, b) ((a) & (1 << (b)))

#define HI(x) ((x)>>8)
#define LO(x) ((x)& 0xFF)


typedef struct {
    uint8_t whole[3];    /*!< Whole part of the number */
    uint8_t pow;         /*!< Power for fractional part */
    uint8_t fraction[3]; /*!<  Fractional part of the number */
} Double, *PDouble;

/**
 * @brief Convert string to Double structure
 * @param[in] pstr - input char string
 * @param[out] stdata - parsed data
 */
void StringToDouble(char* pstr, PDouble stdata);


/**
 * @brief  Set negative flag
 * @param[in,out] stdata
 */
void MakeNegative(PDouble stdata);


/**
 * @brief Convert symbol to number
 * @param[in] ch - symbol
 * @return  number
 */
int8_t getNum(char ch);

/**
 * @brief Parse  string by format
 * @param[in] pbuf - pointer on input buffer
 * @param[in] size - size of buffer
 * @param[in] fmt - pattern for parsing
 * @param[out] ...  - list of arguments
 * @return 
 */
int ParseParameterString(char* pbuf, int size, char* fmt, ...);

#endif // MY_TYPES_H_
