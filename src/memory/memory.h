#ifndef CPP_MAMORY_H
#define CPP_MAMORY_H

#include <iostream>
#include "../logger/logger.h"
#include "../logger/logger_concrete.h"
#include "../logger/logger_builder.h"
#include "../logger/logger_builder_concrete.h"


class memory
{
    public:
        enum class allocate_mode
        {
            first_fit,
            best_fit,
            worst_fit,
        };
    
    public:
        virtual void *allocate(size_t target_size) const = 0;
    
    public:
        virtual void deallocate(void const * const target_to_dealloc) const = 0;
    
    protected:
        virtual void dump_allocate(void *target_ptr, 
                        size_t target_size, 
                        logger *log) const = 0;

    protected:
        virtual std::string get_address(void *target_ptr) const = 0;

    public:
        virtual ~memory() = default;
};

#endif //CPP_MAMORY_H