#ifndef POOL_H
#define POOL_H

#include "memory/memory.h"
#include "trees/BST/associative_container.h"
#include "trees/BST/binary_search_tree.h"
#include "classes/scheme.h"
#include "comparer.h"
#include "logger_singleton.h"

class pool
{
private:
    memory *_allocator;
    associative_container<std::string, scheme> *_pool;

public:
    pool(memory *allocator = nullptr) : _pool(new binary_search_tree<std::string, scheme, string_comparer>()), _allocator(allocator) { logger_singleton::get_instance()->get_logger()->log("Pool constructor", logger::severity::trace); }
    ~pool()
    {
        logger_singleton::get_instance()->get_logger()->log("Pool distructor", logger::severity::trace);
        delete _pool;
    }

    void add(std::string const &name_scheme, scheme &&scheme);
    scheme &find(std::string const &name_scheme);
    memory *get_allocator() { return _allocator; }
    bool find_to_string(std::string const &name_scheme);

public:
    pool(const pool &other)
        : _pool(new binary_search_tree<std::string, scheme, string_comparer>(*reinterpret_cast<binary_search_tree<std::string, scheme, string_comparer> *>(other._pool))), _allocator(other._allocator)
    {
    }

    pool(pool &&other) noexcept
    {
        this->_pool = other._pool;
        this->_allocator = other._allocator;

        other._pool = nullptr;
        other._allocator = nullptr;
    }

    pool &operator=(const pool &other)
    {
        if (this == &other)
        {
            return *this;
        }

        delete this->_pool;

        if (this->_allocator != other._allocator)
        {
            delete this->_allocator;
            this->_allocator = other._allocator;
        }

        this->_pool = new binary_search_tree<std::string, scheme, string_comparer>(*reinterpret_cast<binary_search_tree<std::string, scheme, string_comparer> *>(other._pool));

        return *this;
    }

    pool &operator=(pool &&other) noexcept
    {
        if (this == &other)
        {
            return *this;
        }

        delete this->_pool;
        delete this->_allocator;

        this->_pool = other._pool;
        this->_allocator = other._allocator;

        other._pool = nullptr;
        other._allocator = nullptr;

        return *this;
    }
};

void pool::add(std::string const &name_scheme, scheme &&scheme)
{
    _pool->insert(name_scheme, std::move(scheme));
    std::cout << "gg" << std::endl;
}

scheme &pool::find(std::string const &name_scheme)
{
    return _pool->find(name_scheme);
}

bool pool::find_to_string(std::string const &name_scheme)
{
    return _pool->find_to_string(name_scheme);
}

#endif // POOL_H