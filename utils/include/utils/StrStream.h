#pragma once

#include "utils/FiniteStr.h"
#include "utils/Common.h"
using namespace common;

#include <iostream>

class StrStream : public FiniteStr<>
{
public:
    static constexpr size_t CAPACITY_MAX = 32768 -1;
    
    StrStream() = default;
    StrStream(const StrStream&) = delete;
    StrStream& operator=(const StrStream&) = delete;
    ~StrStream() { clear(); }
    
    void clear()
    {
        FiniteStr<>::clear();
        if (unlikely(strOver_ != nullptr))
        {
            delete [] strOver_;
            strOver_ = nullptr;
        }
    }
    
    const char* c_str() const
    {
        if (likely(strOver_ == nullptr))
        {
            return FiniteStr<>::c_str();
        }
        return strOver_;
    }
    size_t length() const
    {
        if (likely(strOver_ == nullptr))
        {
            return size();
        }
        return sizeOver_;
    }
    
    void append(const char* str, size_t len);
    void append(size_t pos, char c);
    
    //AVOID THIS (use append (faster) or operator<< on const char*)
    StrStream& operator<<(const std::string& str) = delete;
    
    StrStream& operator<<(const char* str);
    StrStream& operator<<(char c);
    
    StrStream& operator<<(const StrStream& strstr);
    
    StrStream& operator<<(std::ostream& ostr);
    friend std::ostream& operator<<(std::ostream&, const StrStream&);
    
    StrStream& operator<<(float flt);
    StrStream& operator<<(double dbl);
    StrStream& operator<<(unsigned int n);
    StrStream& operator<<(unsigned long n);
    StrStream& operator<<(unsigned long long n);
    
private:
    char*  strOver_ = nullptr;
    size_t sizeOver_ = 0;
};
