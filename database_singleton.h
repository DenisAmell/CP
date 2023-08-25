#ifndef DATABASE_SINGLETON_H
#define DATABASE_SINGLETON_H

#include "memory/memory.h"
#include "collections/work_calendar.h"
#include "trees/BST/associative_container.h"
#include "classes/pool.h"
#include "trees/BST/binary_search_tree.h"
#include "comparer.h"
#include "allocators/allocator_type.h"
#include "allocators/global_heap/memory_global_heap.h"
#include "logger_singleton.h"
#include "allocators/memory_list/memory_list.h"
#include <string>
#include <iostream>

class database_singleton
{
public:
    static database_singleton *Instance();
    void add_pool(std::string const &name_pool, allocator_type allocator_type, size_t allocator_size, memory::allocate_mode mode);
    void add_scheme(std::string const &name_pool, std::string const &name_scheme);
    void add_collection(std::string const &name_pool, std::string const &name_scheme, std::string const &name_collection);
    void add_data(std::string const &name_pool, std::string const &name_scheme, std::string const &name_collection, key *data_key, value *data_value);
    void get_data(std::string const &name_pool, std::string const &name_scheme, std::string const &name_collection, key *data_key);
    void get_data_between(std::string const &name_pool, std::string const &name_scheme, std::string const &name_collection, key *left_key, key *right_key);
    void update(std::string const &name_pool, std::string const &name_scheme, std::string const &name_collection, key *data_key);
    void remove_pool(std::string const &name_pool);
    void remove_scheme(std::string const &name_pool, std::string const &name_scheme);
    void remove_collection(std::string const &name_pool, std::string const &name_scheme, std::string const &name_collection);
    void remove_data(std::string const &name_pool, std::string const &name_scheme, std::string const &name_collection, key *data_key, value *data_value);

public:
    database_singleton();
    ~database_singleton()
    {
        delete _database;
    };

    database_singleton(database_singleton const &) = delete;
    database_singleton(database_singleton &&) = delete;
    database_singleton &operator=(database_singleton const &) = delete;
    database_singleton &operator=(database_singleton &&) = delete;

private:
    static database_singleton *_instance;
    associative_container<std::string, pool> *_database;
};

database_singleton *database_singleton::_instance = nullptr;

database_singleton *database_singleton::Instance()
{
    if (_instance == nullptr)
        _instance = new database_singleton;

    return _instance;
}

database_singleton::database_singleton()
{
    _database = new binary_search_tree<std::string, pool, string_comparer>();
    logger_singleton::get_instance()->get_logger()->log("Database constructor", logger::severity::trace);

    //_instance = this;
}

void database_singleton::add_pool(std::string const &name_pool, allocator_type allocator_type, size_t allocator_size, memory::allocate_mode mode)
{
    // TODO: try-catch
    memory *allocator = nullptr;

    switch (allocator_type)
    {
    case allocator_type::GLOBAL_HEAP:
        allocator = new memory_global_heap(logger_singleton::get_instance()->get_logger());
        break;

    case allocator_type::MEMORY_LIST:
        allocator = new memory_list(nullptr, logger_singleton::get_instance()->get_logger(), allocator_size, mode);
        break;
    }

    _database->insert(name_pool, std::move(pool(allocator)));
}

void database_singleton::add_scheme(std::string const &name_pool, std::string const &name_scheme)
{
    // TODO: try-catch
    if (_database->find_to_string(name_pool))
    {
        pool& current_pool = reinterpret_cast<pool&>(_database->find(name_pool));
        current_pool.add(name_scheme, std::move(scheme()));

        //  current_pool.add(name_scheme, std::move(scheme()));
    }
    else
    {
        // TODO: логги, если ничего не найдено
    }
}

void database_singleton::add_collection(std::string const &name_pool, std::string const &name_scheme, std::string const &name_collection)
{
    // // TODO: try-catch
    // if (_database->find_to_string(name_pool))
    // {
    //     pool &current_pool = const_cast<pool &>(_database->get(name_pool));

    //     memory *allocator = current_pool.get_allocator();

    //     if (current_pool.find_to_string(name_scheme))
    //     {
    //         scheme &current_scheme = const_cast<scheme &>(current_pool.get(name_scheme));

    //         current_scheme.add(name_collection, std::move(collection(allocator)));
    //     }
    // }
    // else
    // {
    //     // TODO: логги, если ничего не найдено
    // }
}

void database_singleton::add_data(std::string const &name_pool, std::string const &name_scheme, std::string const &name_collection, key *data_key, value *data_value)
{
    // // TODO: try-catch
    // if (_database->find_to_string(name_pool))
    // {
    //     pool &current_pool = const_cast<pool &>(_database->get(name_pool));

    //     memory *allocator = current_pool.get_allocator();

    //     if (current_pool.find_to_string(name_scheme))
    //     {
    //         scheme &current_scheme = const_cast<scheme &>(current_pool.get(name_scheme));

    //         if (current_scheme.find_to_string(name_collection))
    //         {
    //             collection &current_collection = const_cast<collection &>(current_scheme.get(name_collection));

    //             current_collection.add(data_key, std::move(data_value));
    //         }
    //     }
    // }
    // else
    // {
    //     // TODO: логги, если ничего не найдено
    // }
}

void database_singleton::get_data(std::string const &name_pool, std::string const &name_scheme, std::string const &name_collection, key *data_key)
{
}

void database_singleton::get_data_between(std::string const &name_pool, std::string const &name_scheme, std::string const &name_collection, key *left_key, key *right_key)
{
}

void database_singleton::update(std::string const &name_pool, std::string const &name_scheme, std::string const &name_collection, key *data_key)
{
}

void database_singleton::remove_pool(std::string const &name_pool)
{
}

void database_singleton::remove_scheme(std::string const &name_pool, std::string const &name_scheme)
{
}

void database_singleton::remove_collection(std::string const &name_pool, std::string const &name_scheme, std::string const &name_collection)
{
}

void database_singleton::remove_data(std::string const &name_pool, std::string const &name_scheme, std::string const &name_collection, key *data_key, value *data_value)
{
}

#endif // DATABASE_SINGLETON_H