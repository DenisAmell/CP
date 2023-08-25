#include <iostream>

#include "database_singleton.h"

int main()
{
    database_singleton *database = new database_singleton();
    database->add_pool("aboba", allocator_type::MEMORY_LIST, 100000, memory::allocate_mode::best_fit);

     database->add_scheme("aboba", "lol");
    std::cout << "gg" << std::endl;
    // database->add_collection("aboba", "lol");
    return 0;
}