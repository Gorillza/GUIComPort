#include "MClib/include/common/types.h"

#define FSKIP 0x01
#define FTYPE 0x02

enum { dtUnknown, dtInt, dtUInt, dtLong, dtFloat, dtChar, dtStr, dtDouble };

void StringToDouble(char* pstr, PDouble stdata)
{
    memset(stdata, 0, sizeof(Double));
    uint8_t bfr = 0;
    int32_t whole = 0;
    uint32_t fraction = 0;
    while(*pstr) {
        if(*pstr == '.') {
            bfr = 1;
        } else {
            if(bfr) {
                fraction = fraction * 10 + getNum(*pstr);
                stdata->pow++;
            } else {
                whole = whole * 10 + getNum(*pstr);
            }
        }
        pstr++;
    }

    if(whole) {
        stdata->whole[0] = whole;
        stdata->whole[1] = whole >> 8;
        stdata->whole[2] = whole >> 16;
    }

    if(fraction) {
        stdata->fraction[0] = fraction;
        stdata->fraction[1] = fraction >> 8;
        stdata->fraction[2] = fraction >> 16;
    }
}

void MakeNegative(PDouble stdata)
{
    stdata->whole[2] |= 0x81;
}

int8_t getNum(char ch)
{
    int8_t num = 0;
    if(ch >= '0' && ch <= '9') {
        num = ch - 0x30;
    } else {
        switch(ch) {
        case 'A':
        case 'a':
            num = 10;
            break;
        case 'B':
        case 'b':
            num = 11;
            break;
        case 'C':
        case 'c':
            num = 12;
            break;
        case 'D':
        case 'd':
            num = 13;
            break;
        case 'E':
        case 'e':
            num = 14;
            break;
        case 'F':
        case 'f':
            num = 15;
            break;
        default:
            num = 0;
        }
    }
    return num;
}

int ParseParameterString(char* pbuf, int size, char* fmt, ...)
{
    int result = 0;
    int idx = 0;
    char str[100] = { 0 };
    int datatype = dtUnknown;
    char sep = 0;
    char* pfmt = fmt;
    uint8_t flag = 0;

    va_list vl;
    va_start(vl, fmt);

    while(*pfmt) {
        switch(*pfmt) {
        case '%': {
            sep = 0;
            datatype = dtUnknown;
            flag &= ~FSKIP;
            flag |= FTYPE;
            break;
        }
        case '*': {
            flag |= FSKIP;
            break;
        }
        case 'd': {
            if(flag & FTYPE) {
                datatype = dtInt;
            }
            break;
        }
        case 'l': {
            if(flag & FTYPE) {
                datatype = dtLong;
            }
            break;
        }
        case 'u': {
            if(flag & FTYPE) {
                datatype = dtUInt;
            }
            break;
        }
        case 'f': {
            if(flag & FTYPE) {
                datatype = dtFloat;
            }
            break;
        }
        case 'c': {
            if(flag & FTYPE) {
                datatype = dtChar;
            }
            break;
        }
        case 's': {
            if(flag & FTYPE) {
                datatype = dtStr;
            }
            break;
        }
        case 'g': {
            if(flag & FTYPE) {
                datatype = dtDouble;
            }
            break;
        }

        default: {
            sep = *pfmt;
            flag &= ~FTYPE;
        }
        };
        pfmt++;

        if(datatype == dtUnknown)
            continue;

        if(((flag & FTYPE) == FTYPE) && *pfmt)
            continue;

        idx = 0;
        memset(str, 0, sizeof(str));

        while(*pbuf && *pbuf != sep && size) {
            str[idx++] = *pbuf;
            pbuf++;
            size--;
        }

        pbuf++;
        if((flag & FSKIP) != FSKIP) {
            result++;
            switch(datatype) {
            case dtInt:
            case dtUInt: {
                int* pi;
                pi = va_arg(vl, int*);
                *pi = atoi(str);
                break;
            }
            case dtLong: {
                long* pl;
                pl = va_arg(vl, long*);
                *pl = atol(str);
                break;
            }
            case dtFloat: {
                float* pf;
                pf = va_arg(vl, float*);
                *pf = atof(str);
                break;
            }
            case dtChar: {
                char* pc;
                pc = va_arg(vl, char*);
                *pc = str[0];
                break;
            }
            case dtStr: {
                char* pc;
                pc = va_arg(vl, char*);
                memcpy(pc, str, strlen(str));
                break;
            }
            case dtDouble: {
                PDouble pd;
                pd = va_arg(vl, PDouble);
                StringToDouble(str, pd);
                break;
            }
            }
        }
        datatype = dtUnknown;
        flag = 0;
    }
    va_end(vl);
    return result;
}
