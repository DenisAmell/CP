#ifndef scheme_H
#define scheme_H

#include "memory/memory.h"
#include "classes/collection.h"
#include "../comparer.h"
#include "logger_singleton.h"
#include <iostream>

class scheme
{
private:
    associative_container<std::string, collection> *_scheme;

public:
    scheme(memory *allocator = nullptr) : _scheme(new binary_search_tree<std::string, collection, string_comparer>()) { logger_singleton::get_instance()->get_logger()->log("Scheme constructor", logger::severity::trace); };
    ~scheme()
    {
        logger_singleton::get_instance()->get_logger()->log("Scheme distructor", logger::severity::trace);

        delete _scheme;
    }

    void add(std::string const &name_collection, collection &&collection);
    collection &get(std::string const &name_collection);
    bool find_to_string(std::string const &name_collection);

public:
    scheme(scheme const &other) : _scheme(new binary_search_tree<std::string, collection, string_comparer>(*reinterpret_cast<binary_search_tree<std::string, collection, string_comparer> *>(other._scheme)))
    {
    }

    scheme &operator=(scheme const &other)
    {
        if (this == &other)
        {
            return *this;
        }

        delete this->_scheme;

        this->_scheme = new binary_search_tree<std::string, collection, string_comparer>(*reinterpret_cast<binary_search_tree<std::string, collection, string_comparer> *>(other._scheme));

        return *this;
    }

    scheme(scheme &&other) noexcept
    {
        this->_scheme = other._scheme;
        other._scheme = nullptr;
    }

    scheme &operator=(scheme &&other) noexcept
    {

        if (this == &other)
        {
            return *this;
        }

        delete this->_scheme;

        this->_scheme = other._scheme;

        other._scheme = nullptr;

        return *this;
    }
};

void scheme::add(std::string const &name_collection, collection &&collection)
{
    std::cout << "lol" << std::endl;
    _scheme->insert(name_collection, std::move(collection));
}

collection &scheme::get(std::string const &name_collection)
{
    return _scheme->find(name_collection);
}

bool scheme::find_to_string(std::string const &name_collection)
{
    return _scheme->find_to_string(name_collection);
}

#endif // scheme_H