#pragma once
#include <stdint.h>
#include <string.h>
#include <stdlib.h>


#ifndef MAX_BUFFER_SIZE
#define MAX_BUFFER_SIZE 250
#endif

#if MAX_BUFFER_SIZE < 256
typedef uint8_t TBufferIndex;
#else
#if MAX_BUFFER_SIZE < 65536
typedef uint16_t TBufferIndex;
#else
typedef uint32_t TBufferIndex;
#endif
#endif

//typedef uint32_t TBufferIndex;
class MCBaseBuffer
{
public:
    virtual  bool FifoRead(uint8_t& data){}// = 0;
    virtual  void FifoWrite(uint8_t data){}// = 0;
    virtual  void Clear() {}//= 0;
    virtual  void HardClear(){}// = 0;

    virtual  void Push(uint8_t data) {}//= 0;

    virtual void Push(uint8_t *pdata, TBufferIndex size) {}//= 0;

    virtual  uint8_t * Data() {return nullptr; } //= 0;

    virtual   TBufferIndex Size() {return 0;} //= 0;

    virtual   TBufferIndex Capacity(){return 0;} // = 0;

    virtual   void Erase(TBufferIndex count) {}//= 0;

};

template<TBufferIndex N>
class  MCBuffer : public MCBaseBuffer
{
public:
    const  TBufferIndex m_nSize;       /*!< Buffer size.*/
    const  TBufferIndex m_maskSize;   /*!< Buffer size.*/
    TBufferIndex m_nWriteIndex; /*!< Write index.*/
    TBufferIndex m_nReadIndex;  /*!< Read index.*/
    uint8_t m_Data[N];           /*!< Data array.*/
public:

    MCBuffer():m_nSize(N), m_maskSize(N-1)
    {
     //   memset(m_Data, 0, m_nSize);
        m_nWriteIndex = 0;
        m_nReadIndex = 0;
    }

    ~MCBuffer()
    {
    }

    bool FifoRead(uint8_t& data) override
    {
        if(FifoIsEmpty())
            return false;
        data = m_Data[m_nReadIndex++ & m_maskSize];        
        return true;       
    }

    void FifoWrite(uint8_t data) override
    {
        if(!FifoIsFull())
            m_Data[m_nWriteIndex++ & m_maskSize] = data;
    }


    inline bool FifoIsEmpty()
    {
        return (m_nWriteIndex == m_nReadIndex);
    }


    inline bool FifoIsFull()
    {
        return ((TBufferIndex)(m_nWriteIndex - m_nReadIndex) >= m_nSize);        
    }


    inline void Clear() override
    {
        m_nWriteIndex = 0;
        m_nReadIndex = 0;
    }


    inline void HardClear() override
    {
        Clear();
        memset(m_Data, 0, m_nSize);
    }

    void Push(uint8_t data) override
    {
        if(m_nWriteIndex < m_nSize)
            m_Data[m_nWriteIndex++] = data;
    }

    void Push(uint8_t *pdata, TBufferIndex size) override
    {
        if((TBufferIndex)(m_nWriteIndex + size) < m_nSize) {
            memcpy(&m_Data[m_nWriteIndex], pdata, size);
            m_nWriteIndex += size;
        }
    }


    uint8_t * Data() override
    {
        return m_Data;
    }


    TBufferIndex Size() override
    {
        return m_nWriteIndex;
    }


    void Erase(TBufferIndex count) override
    {
        if(count == 0)
            return;

        if(count >= m_nWriteIndex)
            HardClear();
        else {
            m_nWriteIndex -= count;
            memmove(m_Data, &(m_Data[count]), m_nWriteIndex);
        }
    }


    TBufferIndex Capacity() override
    {
        return m_nSize;
    }

};


