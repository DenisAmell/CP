#ifndef CPP_MAMORY_GLOBAL_HEAP_H
#define CPP_MAMORY_GLOBAL_HEAP_H

#include "../../memory/memory.h"

class memory_global_heap final : public memory
{
    public:
        memory_global_heap(logger *logger);
    public:
        void *allocate(size_t target_size) const override;
    
    public:
        void deallocate(void const * const target_to_dealloc) const override;

    public:
        ~memory_global_heap();

    protected:
        std::string get_address(void *target_ptr) const override;

    protected:
        void dump_allocate(void *target_ptr, 
                        size_t target_size, 
                        logger *log) const override;

    private:
        logger *_log;

};

#endif // CPP_MAMORY_GLOBAL_HEAP_H