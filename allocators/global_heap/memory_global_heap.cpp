#include "memory_global_heap.h"
#include <cstring>
#include <iostream>
#include <string>

memory_global_heap::memory_global_heap(
            logger *logger) : _log(logger) {}

memory_global_heap::~memory_global_heap()
{

}

std::string memory_global_heap::get_address(void *target_ptr) const
{
    char address[20];
    memset(address, 0, 20);
    sprintf(address, "%p", target_ptr);
    std::string add;
    add.append(address);
    return add;
}

void memory_global_heap::dump_allocate(void *target_ptr, 
            size_t target_size, 
            logger *log) const
{
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

void *memory_global_heap::allocate(
            size_t target_size) const
{
    auto *ptr = ::operator new(target_size + sizeof(size_t));
    size_t *ptr_size = reinterpret_cast <size_t*> (ptr);
    *ptr_size = target_size;
    _log->log("Allocate "+ std::to_string(target_size), 
                logger::severity::information);
    return ptr_size + 1;
}

void memory_global_heap::deallocate(void const * const target_to_dealloc) const
{
    auto *ptr = reinterpret_cast<size_t*> (const_cast <void*> (target_to_dealloc)) - 1;
    size_t size = *ptr;
    dump_allocate(const_cast <void*> (target_to_dealloc), size, _log);
    ::operator delete(ptr);
}