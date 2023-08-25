#ifndef CPP_MEMORY_HOLDER_H
#define CPP_MEMORY_HOLDER_H

#include "memory.h"

class memory_holder 
{
    public:
        virtual ~memory_holder() = default;

    protected:
        virtual memory* get_memory() const = 0;

    public:
        void* allocate_with_guard(size_t allocate_size) const;
        void deallocate_with_guard(void* ptr_to_dealloc) const;

};

#endif //CPP_MEMORY_HOLDER_H