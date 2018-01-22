#pragma once

#include <cstddef>
#include <iostream>
#include <stdexcept>

class MemoryBuffer
{
    unsigned char * const data;
    std::size_t const size;
    std::size_t offset;

public:
    explicit MemoryBuffer(std::size_t s)
    : data(static_cast<unsigned char *>(::operator new(s)))
    , size(s)
    , offset(0)
    {}

    MemoryBuffer(MemoryBuffer const &) = delete;
    MemoryBuffer & operator=(MemoryBuffer const &) = delete;

    ~MemoryBuffer()
    {
        ::operator delete(data);
    }

    void * allocate(std::size_t n, std::size_t a)
    {
        offset = (offset + a - 1) / a * a;

        if (offset + n > size)
        {
            throw std::bad_alloc();
        }

        void * result = data + offset;
        offset += n;
        return result;
    }

    void deallocate(void *, std::size_t n) {}
};
