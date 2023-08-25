#include "memory_list.h"
#include <iostream>
#include <cstring>
#include <string>
size_t memory_list::get_service_part_allocator_size() const
{
    return sizeof(memory *) + sizeof(logger *) + sizeof( size_t) + sizeof(allocate_mode) + sizeof(void*);
}

memory_list::memory_list(memory *allocator, 
                    logger *log, 
                    size_t size_allocator, 
                    allocate_mode mode)
{
    size_t all_size = size_allocator + get_service_part_allocator_size();
_alloc = allocator;
    // if (allocator != nullptr)
    // {
    //     _ptr_to_memory = reinterpret_cast<void*>(allocator->allocate(all_size));
    // }
    // else
    // {
    //     _ptr_to_memory = ::operator new(all_size);
    // }

    _ptr_to_memory = this -> allocate_with_guard(all_size);

    auto *ptr_alloc = reinterpret_cast <memory**> (_ptr_to_memory);
    *ptr_alloc = allocator;
    auto *ptr_log = reinterpret_cast<logger**> (ptr_alloc + 1);
    *ptr_log = log;
    auto*ptr_size = reinterpret_cast<size_t*> (ptr_log + 1);
    *ptr_size = size_allocator;
    auto *ptr_mode = reinterpret_cast <memory::allocate_mode*> (ptr_size + 1);
    *ptr_mode = mode;
    auto *first_ptr_availble_block = reinterpret_cast<void**> (ptr_mode + 1);
    *first_ptr_availble_block = reinterpret_cast <unsigned char *> (first_ptr_availble_block) + sizeof(void**);
    auto *last_ptr = reinterpret_cast <size_t*> (*first_ptr_availble_block);
    *last_ptr = size_allocator - sizeof(size_t) - sizeof(void*);
    *(reinterpret_cast <void**> (last_ptr + 1)) = nullptr; 
    this->trace_with_guard("List system allocator initialized");
} 


void * memory_list::get_next_avail_block(void* current_block) const
{
    return *reinterpret_cast <void**> (reinterpret_cast <size_t*> (current_block) + 1);
}

size_t memory_list::get_size_current_block(void* current_block) const
{
    return *(reinterpret_cast <size_t*> (current_block));
}

size_t memory_list::get_service_avail_block_size() const
{
    return sizeof(size_t) + sizeof(void*);
}

size_t memory_list::get_service_occup_block_size() const
{
    return sizeof(size_t);
}

memory::allocate_mode memory_list::get_allocate_mode () const
{
    return *(reinterpret_cast <memory::allocate_mode*> (reinterpret_cast <unsigned char*> (_ptr_to_memory) 
                + sizeof(memory *) + sizeof(logger *) + sizeof( size_t)));
}

void** memory_list::get_first_avail_block_ptr() const
{
    return reinterpret_cast <void**> (reinterpret_cast <unsigned char*> (_ptr_to_memory) 
        + get_service_part_allocator_size() - sizeof(void*));
}

void * memory_list::get_first_avail_block() const
{
    return *get_first_avail_block_ptr();
}

void *memory_list::allocate(size_t target_size) const
{
    auto ovveriden_block_size = target_size;

    if (ovveriden_block_size < sizeof(void*))
        ovveriden_block_size = sizeof(void*);
    

    void* previous_block = nullptr;
    void* current_block = get_first_avail_block();
    void* next_block = nullptr;

    size_t size_current_block;
    auto allocate_mode = get_allocate_mode();
    

    void* previous_target_block = nullptr;
    void* target_block = nullptr;
    void* next_target_block = nullptr;

    
    while (current_block != nullptr)
    {
        next_block = get_next_avail_block(current_block);
        size_current_block = get_size_current_block(current_block);

        if (size_current_block + sizeof(void*) >= ovveriden_block_size)
        {
            if (allocate_mode == memory::allocate_mode::first_fit
                || (allocate_mode == memory::allocate_mode::best_fit && 
                (target_block == nullptr || get_size_current_block(target_block) < get_size_current_block(current_block)))
                || (allocate_mode == memory::allocate_mode::worst_fit && 
                (target_block == nullptr || get_size_current_block(target_block) > get_size_current_block(current_block))))
                //выбор метода подходящего и поиск подходящего
            {
                previous_target_block = previous_block;
                target_block = current_block;
                next_target_block = next_block;
            }

            if (allocate_mode == memory::allocate_mode::first_fit)
                break;
        }
        previous_block = current_block;
        current_block = next_block;
    }

    if (target_block == nullptr) // не найден блок нужного размера
    {
        throw std::bad_alloc();
    }

    size_t target_block_size = get_size_current_block(target_block);
    size_t size_service_avail_block = get_service_avail_block_size();
    size_t size_service_occup_block = get_service_occup_block_size();

    if (target_block_size + sizeof(void*) - ovveriden_block_size < size_service_avail_block)
    {
        ovveriden_block_size = target_block_size + sizeof(void*);
    }

    if (ovveriden_block_size != target_size)
    {
        target_size = ovveriden_block_size;
    }

    void* next_for_previous;

    if (target_block_size + size_service_avail_block == target_block_size + size_service_occup_block)
    {
        next_for_previous = next_target_block;
    }
    else
    {
        next_for_previous = reinterpret_cast <unsigned char*> (target_block) + target_size + sizeof(size_t);
        *reinterpret_cast <size_t*> (next_for_previous) = target_block_size - target_size - sizeof(size_t);
        *reinterpret_cast <void**> (reinterpret_cast<size_t*> (next_for_previous) + 1) = next_target_block;
    }

    if (previous_target_block == nullptr) //нет прерыдущего блока [ ][  ] -> [//][  ]
    {
        *get_first_avail_block_ptr() = next_for_previous;
    }
    else // [  ][ ][   ] -> [  ][//][   ]
    {
        *reinterpret_cast <void**> (reinterpret_cast <size_t*> (previous_target_block) + 1) = 
            next_for_previous;
    }


    *(reinterpret_cast <size_t*> (target_block)) = target_size;
    dump_allocator_state(true);
    return reinterpret_cast <void*> (reinterpret_cast <size_t*> (target_block) + 1);
}

size_t memory_list::get_allocator_size() const
{
    return *reinterpret_cast <size_t*> (reinterpret_cast <unsigned char*> (_ptr_to_memory) + sizeof(memory*) + sizeof(logger*));
}

memory* memory_list::get_memory() const
{
    return _alloc;
}

void memory_list::deallocate(void const * const target_to_dealloc) const
{
    void* true_block_ptr = reinterpret_cast <void*> (reinterpret_cast <unsigned char*> 
        (const_cast <void *> (target_to_dealloc)) - sizeof(size_t));
    debug_allocate(true_block_ptr);

    void* previous_block = nullptr;
    void* current_block = get_first_avail_block();

    if (true_block_ptr < reinterpret_cast <unsigned char*> (_ptr_to_memory) + get_service_part_allocator_size()
        || true_block_ptr >= reinterpret_cast <unsigned char*> (_ptr_to_memory) + get_service_part_allocator_size() + get_allocator_size() - get_service_avail_block_size())
    {
        throw std::exception();
    }

    while (current_block < target_to_dealloc) // поиск нужного блока для очистки
    {
        previous_block = current_block;
        current_block = get_next_avail_block(current_block);
    }

    size_t size_block_deallocate = get_size_current_block(true_block_ptr);

    if (previous_block == nullptr && current_block == nullptr) // нужно освободить всю память [////] -> [    ]
    {
        *(reinterpret_cast <void**> (const_cast <void *> (target_to_dealloc))) = nullptr;
        *get_first_avail_block_ptr() = true_block_ptr;
    }
    else
    {
        if (current_block == nullptr ) // && previuos != nullptr  [   ][///] -> [       ]
        {
            *(reinterpret_cast <void**> (const_cast <void *> (target_to_dealloc))) = nullptr;
            size_block_deallocate = *(reinterpret_cast <size_t*> (true_block_ptr)) 
                                    = size_block_deallocate - sizeof(void*);
        }
        else // previous_block == nullptr && current_block != nullptr
        {
            if (reinterpret_cast <unsigned char*> (const_cast <void*> (target_to_dealloc)) + size_block_deallocate == current_block)
            {
                *(reinterpret_cast <void**> (reinterpret_cast <size_t*> (true_block_ptr) + 1)) = get_next_avail_block(current_block);
                size_block_deallocate = *(reinterpret_cast <size_t*> (true_block_ptr)) = size_block_deallocate + get_size_current_block(current_block) + sizeof(size_t);
                current_block = true_block_ptr;                
            }
            else 
            {
                *(reinterpret_cast <void**> (reinterpret_cast <size_t*> (true_block_ptr) + 1)) = current_block;
                size_block_deallocate = *(reinterpret_cast <size_t*> (true_block_ptr)) = size_block_deallocate - sizeof(void*);
            }
        }

        if (previous_block == nullptr) // && current != nullptr  
        {
            *get_first_avail_block_ptr() = true_block_ptr;            
        }
        else //current_block == nullptr && previous_block != nullptr
        {
            size_t previous_size_block = get_size_current_block(previous_block);
            if (reinterpret_cast <unsigned char*> (previous_block) + get_service_avail_block_size() + previous_size_block == true_block_ptr)
            {
                *(reinterpret_cast <void**> (reinterpret_cast <size_t*> (previous_block) + 1)) 
                                        = get_next_avail_block(true_block_ptr);
                *(reinterpret_cast <size_t*> (previous_block)) = previous_size_block 
                                        + size_block_deallocate + get_service_avail_block_size();
            }
            else
            {
                *(reinterpret_cast <void**> (reinterpret_cast <size_t*> (previous_block) + 1)) 
                                        = true_block_ptr;
            }
        }
    }
    dump_allocator_state(false);
}

memory_list::~memory_list()
{
    if (_ptr_to_memory == nullptr)
        return;

    logger* log = get_logger();
    memory* allocator = *(reinterpret_cast <memory**> (_ptr_to_memory));
    if (allocator != nullptr)
        allocator->deallocate(_ptr_to_memory);
    else
        ::operator delete(_ptr_to_memory);

    
    if (log != nullptr)
        log->log("Destructor executed successfully", logger::severity::trace); 
}

std::string memory_list::get_address(void *target_ptr) const
{
    char address[20];
    memset(address, 0, 20);
    sprintf(address, "%p", target_ptr);
    std::string add;
    add.append(address);
    return add;
}

    
void memory_list::debug_allocate(void *target_ptr) const
{
    logger* log = get_logger();
    if (log == nullptr)
        return;
    size_t target_size = get_size_current_block(target_ptr);
    std::string address = get_address(target_ptr);
    std::string buff;
    auto ptr = reinterpret_cast <unsigned char*> (target_ptr);
    for (int i = 0; i < target_size; i++)
    {
        unsigned short add = static_cast <unsigned short> (*ptr);
        buff.append(std::to_string(add)+ ' ');
        ptr++;
    }
    log->log("Block at address " + address + " state before deallocation: \n [" + buff + "]", logger::severity::information);
}

logger* memory_list::get_logger() const
{
    return *(reinterpret_cast <logger**> (reinterpret_cast <unsigned char*> (_ptr_to_memory) 
                + sizeof(memory *)));
}

void memory_list::dump_allocator_state(bool is_allocate) const noexcept
{
    auto *log = get_logger();
    if (log == nullptr)
    {

        return;
    }

    auto allocator_memory_size = *(reinterpret_cast <size_t*> (reinterpret_cast <unsigned char*> (_ptr_to_memory) 
                + sizeof(memory *) + sizeof(logger *)));

    std::string constructed_state_string("|");
    auto *current_aviable_block = get_first_avail_block();
    auto *current_any_block = reinterpret_cast<unsigned char *>(_ptr_to_memory) + get_service_part_allocator_size();

    while (current_any_block - reinterpret_cast<unsigned char *>(_ptr_to_memory) < allocator_memory_size)
    {
        size_t any_block_size = 0;
        if (current_any_block == current_aviable_block)
        {
            constructed_state_string += "avlbl " + std::to_string(any_block_size = get_size_current_block(current_any_block)) + '|';
            any_block_size += get_service_avail_block_size();
            current_aviable_block = get_next_avail_block(current_aviable_block);
        }
        else
        {
            constructed_state_string += "occpd " + std::to_string(any_block_size = get_size_current_block(current_any_block)) + '|';
            any_block_size += sizeof(size_t);
        }

        current_any_block += any_block_size;
    }

    log->log(std::string("Memory state after ") + (is_allocate ? "" : "de") + "allocation operation: " + constructed_state_string, logger::severity::trace);
}

void memory_list::dump_allocate(void *target_ptr, 
                        size_t target_size, 
                        logger *log) const
{

}