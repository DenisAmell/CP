#ifndef CPP_MEMORY_LIST_H
#define CPP_MEMORY_LIST_H

#include "../../memory/memory.h"
#include "../../logger/logger_holder.h"
#include "../../memory/memory_holder.h"

class memory_list final : public memory, protected logger_holder, protected memory_holder
{
    public:
        memory_list(memory *allocator, 
                    logger *log, 
                    size_t size_allocator, 
                    allocate_mode mode);

    public:
        void *allocate(size_t target_size) const override;
    
    protected:
        size_t get_service_part_allocator_size() const;
        void * get_next_avail_block(void* current_block) const;
        void * get_first_avail_block() const;
        size_t get_size_current_block(void* current_block) const;
        size_t get_service_avail_block_size() const;
        size_t get_service_occup_block_size() const;
        memory::allocate_mode get_allocate_mode () const;
        void** get_first_avail_block_ptr() const;
        void dump_allocator_state(bool is_allocate) const noexcept;
        logger* get_logger() const override;
        size_t get_allocator_size() const;
        memory* get_memory() const override;

    public:
        void deallocate(void const * const target_to_dealloc) const override;

    public:
        ~memory_list();

    protected:
        std::string get_address(void *target_ptr) const override;

    protected:
        void debug_allocate(void *target_ptr) const;
        void dump_allocate(void *target_ptr, 
                        size_t target_size, 
                        logger *log) const override;

    private:
        void *_ptr_to_memory;
        memory * _alloc;
};

#endif // CPP_MEMORY_LIST_H